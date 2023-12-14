#include <stdio.h>
#include <string.h>

#define MAX_COURTS 8//一共8场
#define MAX_RESERVATIONS 4//在一个时间段全约满了是4
#define MAX_RESERVATION 100000//最大预约容量
#define MAX_NAME_LENGTH 50
#define MAX_PHONE_LENGTH 20
#define MAX_ID_LENGTH 15
#define FILENAME "reservations.txt"

typedef struct {
    int courtNumber;
    int availableCount;
    int reservedCount;
} Court;

typedef struct {
    int courtNumber;
    int day;
    int hour;
    int availableCount;
    int reservedCount;
    char id[MAX_ID_LENGTH];//用来记录学号
    char name[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH];
} Reservation;

Court courts[MAX_COURTS];
Reservation reservations[MAX_RESERVATION];
int numReservations = 0;

void saveReservationsToFile() {
    FILE *file = fopen(FILENAME, "w");//直接覆盖写入。否则全都不对了

    if (file == NULL) {
        printf("无法打开文件。\n");
        return;
    }

    for (int i = 0; i < numReservations; i++) {
        fprintf(file, "%d %d %d %s %s %s \n", reservations[i].courtNumber, reservations[i].day, reservations[i].hour, reservations[i].id, reservations[i].name,
                reservations[i].phone);//预约数全部写进文件
    }

    fclose(file);
}

void loadReservationsFromFile() {
    FILE *file = fopen(FILENAME, "r");

    if (file == NULL) {
        return;
    }

    numReservations = 0;

    while (fscanf(file, "%d %d %d %s %s %s\n", &reservations[numReservations].courtNumber,
                  &reservations[numReservations].day, &reservations[numReservations].hour, reservations[numReservations].id,
                  reservations[numReservations].name, reservations[numReservations].phone) == 6) {
        numReservations++;
    }//读到6条信息就跳下一个格子

    fclose(file);
}
void initialize(){
    for (int i = 0; i < MAX_COURTS; i++) {
        courts[i].courtNumber = i + 1;
        courts[i].availableCount = 4;
        courts[i].reservedCount = 0;
    }
}

void displayCourts() {
    printf("请输入星期几（0代表星期日，1代表星期一，以此类推）：");
    int selectedDay;
    int availableCount, reservedCount, courtNumber;
    scanf("%d", &selectedDay);
    int start, times = 0;
    // 计算要展示的三天日期
    const int numDays = 3;
    int daysToDisplay[numDays];
    for (int i = 0; i < numDays; i++) {
        daysToDisplay[i] = (selectedDay + i) % 7;
    }

    // 打开文件进行读取在主体部分

    // 展示可预约时间段的场地信息
    printf("注：星期一、三、五17:00-20:00为教工羽协活动时间。\n场次信息如下：）\n");
    for (int i = 0; i < numDays; i++) {
        int dayToDisplay = daysToDisplay[i];
        switch(dayToDisplay)
        {
        case 1:
            printf("星期一");
            break;
        case 2:
            printf("星期二");
            break;
        case 3:
            printf("星期三");
            break;
        case 4:
            printf("星期四");
            break;
        case 5:
            printf("星期五");
            break;
        case 6:
            printf("星期六");
            break;
        default:
            printf("星期日");
            break;
        }
        if(daysToDisplay[i] >= 1 && daysToDisplay[i] <= 5)
            start = 15;
        else
            start = 9;

        for (int hour = start; hour <= 20; hour++) {
            if((dayToDisplay == 1 || dayToDisplay == 3 || dayToDisplay == 5) && (hour >= 17 && hour < 20))
                    continue;
            else
                printf("\n时间段：%02d:00-%02d:00 \n\n", hour, hour + 1);//再输出时间段
            // 查找对应时间段的场地信息（改一下显示）
            initialize();//初始化本时间段的所有的场地信息
            for (int k = 0; k < numReservations; k++) {//读取所有符合时间段的预约信息
                int courtNumber = reservations[k].courtNumber;
                int reservedCount = 0;
                for(int j = 0; j < numReservations; j++){
                    if (reservations[j].courtNumber == courtNumber && reservations[j].day == dayToDisplay && reservations[j].hour == hour) {
                        reservedCount++;//如果信息相同（特别是时间段相同），预定增加。
                    }
                }

                int availableCount = MAX_RESERVATIONS - reservedCount;

                courts[courtNumber-1].availableCount = availableCount;
                courts[courtNumber-1].reservedCount = reservedCount;//只存一份，如果预定了就输出他。
            }
            for(int i = 0; i < MAX_COURTS; i++)
            {
                    printf("场地%d 可预约数：%d 已预约数：%d", courts[i].courtNumber, courts[i].availableCount, courts[i].reservedCount);
                    times++;
                if(courts[i].availableCount == 0)
                    printf("（已订满） ");
                else
                    printf("\t\t");

                if(times == 2)
                {
                    printf("\n\n");
                    times = 0;
                }
            }
        }
        printf("\n");
    }
}

void displayReservations() {
    printf("预约信息：\n");

    for (int i = 0; i < numReservations; i++) {
        int courtNumber = reservations[i].courtNumber;
        int day = reservations[i].day;
        int hour = reservations[i].hour;

        // 检查是否已经显示过相同时间的相同场次
        int alreadyDisplayed = 0;

        for (int j = 0; j < i; j++) {
            if (reservations[j].courtNumber == courtNumber && reservations[j].day == day && reservations[j].hour == hour) {
                alreadyDisplayed = 1;
                break;
            }
        }

        if (alreadyDisplayed) {
            continue;//跳过？
        }

        // 统计预定场次数和剩余场次数
        int reservedCount = 0;

        for (int j = i; j < numReservations; j++) {
            if (reservations[j].courtNumber == courtNumber && reservations[j].day == day && reservations[j].hour == hour) {
                reservedCount++;
            }//从i开始遍历预约结构，只要和要求一样的就计数，如果出现了就跳过它。
        }

        int availableCount = MAX_RESERVATIONS - reservedCount;
        switch(day)
        {
        case 1:
            printf("星期一 ");
            break;
        case 2:
            printf("星期二 ");
            break;
        case 3:
            printf("星期三 ");
            break;
        case 4:
            printf("星期四 ");
            break;
        case 5:
            printf("星期五 ");
            break;
        case 6:
            printf("星期六 ");
            break;
        default:
            printf("星期日 ");
            break;
        }
        printf("场地%d 时间：%02d:00-%02d:00 可预约数：%d 已预约数：%d",
              courtNumber, hour, hour + 1, availableCount, reservedCount);

        if (reservedCount >= MAX_RESERVATIONS) {
            printf("（已订满）");
        }

        printf("\n");
    }
}

void searchByCourt() {
    int courtNumber;

    printf("请输入要查询的场地编号：");
    scanf("%d", &courtNumber);

    printf("场地%d的预约信息：\n", courtNumber);

    int found = 0;

    for (int i = 0; i < numReservations; i++) {
        if (reservations[i].courtNumber == courtNumber) {
            printf("预约编号：%d\n", i + 1);
            printf("日期和时间：星期%d %02d:00\n", reservations[i].day, reservations[i].hour);
            printf("学号（工号）：%s\n", reservations[i].id);
            printf("姓名：%s\n", reservations[i].name);
            printf("联系电话：%s\n", reservations[i].phone);
            printf("--------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("该场地暂无预约信息。\n");
    }
}

void searchByPhone() {
    char phone[MAX_PHONE_LENGTH];

    printf("请输入要查询的手机号：");
    scanf("%s", phone);

    printf("手机号%s的预约信息：\n", phone);

    int found = 0;

    for (int i = 0; i < numReservations; i++) {
        if (strcmp(reservations[i].phone, phone) == 0) {
            printf("预约编号：%d\n", i + 1);
            printf("场地编号：%d\n", reservations[i].courtNumber);
            printf("日期和时间：星期%d %02d:00\n", reservations[i].day, reservations[i].hour);
            printf("工号（学号）：%s\n", reservations[i].id);
            printf("姓名：%s\n", reservations[i].name);
            printf("--------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("该手机号暂无预约信息。\n");
    }
}

void cancelReservation() {
    int reservationNumber;

    printf("请输入要取消的预约编号（可以通过查询预约电话或场次得到预约编号）：");
    scanf("%d", &reservationNumber);

    if (reservationNumber < 1 || reservationNumber > numReservations) {
        printf("无效的预约编号。\n");
        return;
    }

    // 将预约记录数组中的预约信息删除
    for (int i = reservationNumber - 1; i < numReservations - 1; i++) {
        reservations[i] = reservations[i + 1];
    }

    numReservations--;

    // 保存更新后的预约记录到文件
    saveReservationsToFile();

    printf("预约已取消。\n");
}

void addReservation() {
    printf("请输入预约信息：\n");

    int courtNumber, day, hour;
    char id[MAX_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char phoneNumber[MAX_PHONE_LENGTH];

    printf("场地编号（1-8）：");
    scanf("%d", &courtNumber);

    printf("时间（星期几）：");
    scanf("%d", &day);

    printf("时间段（24小时制）：\n");
    printf("可预约时间为星期一到星期五15：00-21：00，星期六、日6：00-21：00\n");
    printf("注意：星期一、三、五17：00-20：00为教工羽协活动时间，不可预约。\n");
    scanf("%d", &hour);
    if((day == 1 || day == 3 || day == 5) && (hour >= 17 && hour < 20))
    {
        printf("该时间段为教工活动时间，不可预约\n");
        return ;
    }
    if (((day >= 1 && day <= 5) && (hour >= 15 && hour <= 20)) ||
        ((day == 6 || day == 7)&& (hour >= 9 && hour <= 20))) {
        printf("工号/学号：");
        scanf("%s", id);
        printf("姓名：");
        scanf("%s", name);
        printf("联系电话：");
        scanf("%s", phoneNumber);

    // 检查是否在规定的预约时间范围内


        // 检查是否已存在相同的预约记录
        for (int i = 0; i < numReservations; i++) {
            if (reservations[i].day == day && reservations[i].hour == hour &&
                strcmp(reservations[i].phone, phoneNumber) == 0 && strcmp(reservations[i].name, name) == 0 && strcmp(reservations[i].id, id) == 0) {
                printf("同一人不能在同一时间段再次预约。\n");
                return; // 预约失败，返回
            }
        }

        // 检查单个场地在单个时间段内的预定次数是否超过4次
        int reservationCount = 0;

        for (int i = 0; i < numReservations; i++) {
            if (reservations[i].courtNumber == courtNumber && reservations[i].day == day && reservations[i].hour == hour) {
                reservationCount++;

                if (reservationCount >= MAX_RESERVATIONS) {
                    printf("该场地在该时间段内预定次数已满，请选择其他时间段或场地。\n");
                    return; // 预约失败，返回
                }
            }
        }

        // 保存预约信息
        reservations[numReservations].courtNumber = courtNumber;
        reservations[numReservations].day = day;
        reservations[numReservations].hour = hour;
        strcpy(reservations[numReservations].id, id);
        strcpy(reservations[numReservations].name, name);
        strcpy(reservations[numReservations].phone, phoneNumber);

        numReservations++;


        saveReservationsToFile();//更新的数据全部写入。
        printf("预约成功！\n");
        return; // 预约成功，返回
    }
    else {
        printf("不在预定时间内，不可预定。\n");
        return; // 预约失败，返回
    }
}


int main() {
    // 初始化场地信息
    for (int i = 0; i < MAX_COURTS; i++) {
        courts[i].courtNumber = i + 1;
        courts[i].availableCount = 4;
        courts[i].reservedCount = 0;
    }

    // 从文件加载预约记录，文件的内容转存到结构体里）
    //补充在功能中的保存函数使得结构体的内容转回文件中保存。
    loadReservationsFromFile();

    int choice;

    do {
        printf("\n欢迎使用预约系统！\n");
        printf("1. 显示场地信息\n");
        printf("2. 显示预约信息\n");
        printf("3. 查询场地预约信息\n");
        printf("4. 查询手机号预约信息\n");
        printf("5. 取消预约\n");
        printf("6. 添加预约\n");
        printf("0. 退出\n");
        printf("请输入您的选择：");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayCourts();
                break;
            case 2:
                displayReservations();
                break;
            case 3:
                searchByCourt();
                break;
            case 4:
                searchByPhone();
                break;
            case 5:
                cancelReservation();
                break;
            case 6:
                addReservation();
                break;
            case 0:
                printf("感谢使用预约系统，再见！\n");
                break;
            default:
                printf("无效的选择，请重新输入。\n");
                break;
        }
    } while (choice != 0);

    return 0;
}
