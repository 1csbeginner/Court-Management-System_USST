#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_NAME_LENGTH 10000
#define MAX_PHONE_LENGTH 20
#define MAX_BOOKINGS 8

typedef struct {
    int courtNumber;                // 场地编号
    char bookedBy[MAX_NAME_LENGTH]; // 预约人姓名
    char contactPhone[MAX_PHONE_LENGTH]; // 预约人联系电话
} Booking;

typedef struct {
    Booking bookings[MAX_BOOKINGS]; // 场地预约信息数组
    int day;
    int month;
    int year;
} CourtSchedule;

void initializeSchedule(CourtSchedule schedule[], int numDays) {
    for (int i = 0; i < numDays; i++) {
        for (int j = 0; j < MAX_BOOKINGS; j++) {
            schedule[i].bookings[j].courtNumber = 0;
            strcpy(schedule[i].bookings[j].bookedBy, "");
            strcpy(schedule[i].bookings[j].contactPhone, "");
        }
        schedule[i].day = 0;
        schedule[i].month = 0;
        schedule[i].year = 0;
    }
}

void displayCourtSchedule(CourtSchedule schedule[], int numDays) {
    printf("场地预约表:\n");
    for (int i = 0; i < numDays; i++) {
        printf("日期: %04d/%02d/%02d\n", schedule[i].year, schedule[i].month, schedule[i].day);
        printf("场地\t预约人\t电话\n");
        for (int j = 0; j < MAX_BOOKINGS; j++) {
            printf("%d\t%s\t%s\n", schedule[i].bookings[j].courtNumber,
                   schedule[i].bookings[j].bookedBy,
                   schedule[i].bookings[j].contactPhone);
        }
        printf("\n");
    }
}

int isBookingSlotAvailable(CourtSchedule schedule[], int day, int courtNumber) {
    if (schedule[day].bookings[courtNumber - 1].courtNumber == 0) {
        return 1; // Booking slot is available
    }
    return 0; // Booking slot is already taken
}//检查是否可用

void makeBooking(CourtSchedule schedule[], int day, int courtNumber, const char* bookedBy, const char* contactPhone) {
    schedule[day].bookings[courtNumber - 1].courtNumber = courtNumber;
    strcpy(schedule[day].bookings[courtNumber - 1].bookedBy, bookedBy);
    strcpy(schedule[day].bookings[courtNumber - 1].contactPhone, contactPhone);
}//下订单

void cancelBooking(CourtSchedule schedule[], int day, int courtNumber) {
    schedule[day].bookings[courtNumber - 1].courtNumber = 0;
    strcpy(schedule[day].bookings[courtNumber - 1].bookedBy, "");
    strcpy(schedule[day].bookings[courtNumber - 1].contactPhone, "");
}//取消（删除）

int main() {
    SetConsoleOutputCP(65001); //输入中文不会出现乱码
    int numDays = 3; // Number of days to display in the schedule
    CourtSchedule schedule[numDays];

    initializeSchedule(schedule, numDays);

    /* 使用例子
    makeBooking(schedule, 0, 2, "狂魔哥", "1234567890");
    makeBooking(schedule, 1, 4, "畜生抱枕样", "9876543210");


    displayCourtSchedule(schedule, numDays);

    cancelBooking(schedule, 0, 2);

    displayCourtSchedule(schedule, numDays);*/
    //我自己写的界面程序
    printf("                欢迎使用羽毛球馆预约系统                 \n");
    printf("                1.预定                                   \n");
    printf("                2.查询                                   \n");
    printf("                3.修改信息                               \n");
    printf("                4.取消预订                               \n");
    int a, i = 0, j = 0;//输入选项，i表示日期，j表示表的第几项
    scanf("%d", &a);

    switch (a)
    {
    case 1:
        {
            printf("输入预定场地，姓名，联系电话");
            Booking* p = (Booking*)malloc(sizeof(Booking));
            scanf("%d %s %s", &p->courtNumber, p->bookedBy, p->contactPhone);//读入场地姓名电话
            //printf("%d %s %s", p->courtNumber, p->bookedBy, p->contactPhone);//只能显示英语，汉字显示不了->读入数据没有问题
            /*检查一下有没有重复，有重复就退出来重新选*/
            for(j = 0; j < MAX_BOOKINGS; j++)
            {
                if()
            }
            makeBooking(schedule, i, p->courtNumber, p->bookedBy, p->contactPhone);
            i++;
            if(p)
            {
                free(p);
                p = NULL;
            }
            break;
        }
    case 2:
        {
            displayCourtSchedule(schedule, numDays);
            break;
        }
    case 3:
        {
            printf("重新输入预定场地，姓名，联系电话");
            Booking* p = (Booking*)malloc(sizeof(Booking));
            scanf("%d %s %s", &p->courtNumber, p->bookedBy, p->contactPhone);//读入场地姓名电话
            printf("%d %s %s", p->courtNumber, p->bookedBy, p->contactPhone);//只能显示英语，汉字显示不了
            if(p)
            {
                free(p);
                p = NULL;
            }
            break;
        }
    case 4:
        {
            cancelBooking(schedule, 0, 2);
            break;
        }
    default:
        printf("重新输入");
        break;

    }

    return 0;
}
