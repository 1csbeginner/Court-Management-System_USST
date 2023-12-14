#include <stdio.h>
#include <string.h>

#define MAX_COURTS 8//һ��8��
#define MAX_RESERVATIONS 4//��һ��ʱ���ȫԼ������4
#define MAX_RESERVATION 100000//���ԤԼ����
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
    char id[MAX_ID_LENGTH];//������¼ѧ��
    char name[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH];
} Reservation;

Court courts[MAX_COURTS];
Reservation reservations[MAX_RESERVATION];
int numReservations = 0;

void saveReservationsToFile() {
    FILE *file = fopen(FILENAME, "w");//ֱ�Ӹ���д�롣����ȫ��������

    if (file == NULL) {
        printf("�޷����ļ���\n");
        return;
    }

    for (int i = 0; i < numReservations; i++) {
        fprintf(file, "%d %d %d %s %s %s \n", reservations[i].courtNumber, reservations[i].day, reservations[i].hour, reservations[i].id, reservations[i].name,
                reservations[i].phone);//ԤԼ��ȫ��д���ļ�
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
    }//����6����Ϣ������һ������

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
    printf("���������ڼ���0���������գ�1��������һ���Դ����ƣ���");
    int selectedDay;
    int availableCount, reservedCount, courtNumber;
    scanf("%d", &selectedDay);
    int start, times = 0;
    // ����Ҫչʾ����������
    const int numDays = 3;
    int daysToDisplay[numDays];
    for (int i = 0; i < numDays; i++) {
        daysToDisplay[i] = (selectedDay + i) % 7;
    }

    // ���ļ����ж�ȡ�����岿��

    // չʾ��ԤԼʱ��εĳ�����Ϣ
    printf("ע������һ��������17:00-20:00Ϊ�̹���Э�ʱ�䡣\n������Ϣ���£���\n");
    for (int i = 0; i < numDays; i++) {
        int dayToDisplay = daysToDisplay[i];
        switch(dayToDisplay)
        {
        case 1:
            printf("����һ");
            break;
        case 2:
            printf("���ڶ�");
            break;
        case 3:
            printf("������");
            break;
        case 4:
            printf("������");
            break;
        case 5:
            printf("������");
            break;
        case 6:
            printf("������");
            break;
        default:
            printf("������");
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
                printf("\nʱ��Σ�%02d:00-%02d:00 \n\n", hour, hour + 1);//�����ʱ���
            // ���Ҷ�Ӧʱ��εĳ�����Ϣ����һ����ʾ��
            initialize();//��ʼ����ʱ��ε����еĳ�����Ϣ
            for (int k = 0; k < numReservations; k++) {//��ȡ���з���ʱ��ε�ԤԼ��Ϣ
                int courtNumber = reservations[k].courtNumber;
                int reservedCount = 0;
                for(int j = 0; j < numReservations; j++){
                    if (reservations[j].courtNumber == courtNumber && reservations[j].day == dayToDisplay && reservations[j].hour == hour) {
                        reservedCount++;//�����Ϣ��ͬ���ر���ʱ�����ͬ����Ԥ�����ӡ�
                    }
                }

                int availableCount = MAX_RESERVATIONS - reservedCount;

                courts[courtNumber-1].availableCount = availableCount;
                courts[courtNumber-1].reservedCount = reservedCount;//ֻ��һ�ݣ����Ԥ���˾��������
            }
            for(int i = 0; i < MAX_COURTS; i++)
            {
                    printf("����%d ��ԤԼ����%d ��ԤԼ����%d", courts[i].courtNumber, courts[i].availableCount, courts[i].reservedCount);
                    times++;
                if(courts[i].availableCount == 0)
                    printf("���Ѷ����� ");
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
    printf("ԤԼ��Ϣ��\n");

    for (int i = 0; i < numReservations; i++) {
        int courtNumber = reservations[i].courtNumber;
        int day = reservations[i].day;
        int hour = reservations[i].hour;

        // ����Ƿ��Ѿ���ʾ����ͬʱ�����ͬ����
        int alreadyDisplayed = 0;

        for (int j = 0; j < i; j++) {
            if (reservations[j].courtNumber == courtNumber && reservations[j].day == day && reservations[j].hour == hour) {
                alreadyDisplayed = 1;
                break;
            }
        }

        if (alreadyDisplayed) {
            continue;//������
        }

        // ͳ��Ԥ����������ʣ�ೡ����
        int reservedCount = 0;

        for (int j = i; j < numReservations; j++) {
            if (reservations[j].courtNumber == courtNumber && reservations[j].day == day && reservations[j].hour == hour) {
                reservedCount++;
            }//��i��ʼ����ԤԼ�ṹ��ֻҪ��Ҫ��һ���ľͼ�������������˾���������
        }

        int availableCount = MAX_RESERVATIONS - reservedCount;
        switch(day)
        {
        case 1:
            printf("����һ ");
            break;
        case 2:
            printf("���ڶ� ");
            break;
        case 3:
            printf("������ ");
            break;
        case 4:
            printf("������ ");
            break;
        case 5:
            printf("������ ");
            break;
        case 6:
            printf("������ ");
            break;
        default:
            printf("������ ");
            break;
        }
        printf("����%d ʱ�䣺%02d:00-%02d:00 ��ԤԼ����%d ��ԤԼ����%d",
              courtNumber, hour, hour + 1, availableCount, reservedCount);

        if (reservedCount >= MAX_RESERVATIONS) {
            printf("���Ѷ�����");
        }

        printf("\n");
    }
}

void searchByCourt() {
    int courtNumber;

    printf("������Ҫ��ѯ�ĳ��ر�ţ�");
    scanf("%d", &courtNumber);

    printf("����%d��ԤԼ��Ϣ��\n", courtNumber);

    int found = 0;

    for (int i = 0; i < numReservations; i++) {
        if (reservations[i].courtNumber == courtNumber) {
            printf("ԤԼ��ţ�%d\n", i + 1);
            printf("���ں�ʱ�䣺����%d %02d:00\n", reservations[i].day, reservations[i].hour);
            printf("ѧ�ţ����ţ���%s\n", reservations[i].id);
            printf("������%s\n", reservations[i].name);
            printf("��ϵ�绰��%s\n", reservations[i].phone);
            printf("--------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("�ó�������ԤԼ��Ϣ��\n");
    }
}

void searchByPhone() {
    char phone[MAX_PHONE_LENGTH];

    printf("������Ҫ��ѯ���ֻ��ţ�");
    scanf("%s", phone);

    printf("�ֻ���%s��ԤԼ��Ϣ��\n", phone);

    int found = 0;

    for (int i = 0; i < numReservations; i++) {
        if (strcmp(reservations[i].phone, phone) == 0) {
            printf("ԤԼ��ţ�%d\n", i + 1);
            printf("���ر�ţ�%d\n", reservations[i].courtNumber);
            printf("���ں�ʱ�䣺����%d %02d:00\n", reservations[i].day, reservations[i].hour);
            printf("���ţ�ѧ�ţ���%s\n", reservations[i].id);
            printf("������%s\n", reservations[i].name);
            printf("--------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("���ֻ�������ԤԼ��Ϣ��\n");
    }
}

void cancelReservation() {
    int reservationNumber;

    printf("������Ҫȡ����ԤԼ��ţ�����ͨ����ѯԤԼ�绰�򳡴εõ�ԤԼ��ţ���");
    scanf("%d", &reservationNumber);

    if (reservationNumber < 1 || reservationNumber > numReservations) {
        printf("��Ч��ԤԼ��š�\n");
        return;
    }

    // ��ԤԼ��¼�����е�ԤԼ��Ϣɾ��
    for (int i = reservationNumber - 1; i < numReservations - 1; i++) {
        reservations[i] = reservations[i + 1];
    }

    numReservations--;

    // ������º��ԤԼ��¼���ļ�
    saveReservationsToFile();

    printf("ԤԼ��ȡ����\n");
}

void addReservation() {
    printf("������ԤԼ��Ϣ��\n");

    int courtNumber, day, hour;
    char id[MAX_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char phoneNumber[MAX_PHONE_LENGTH];

    printf("���ر�ţ�1-8����");
    scanf("%d", &courtNumber);

    printf("ʱ�䣨���ڼ�����");
    scanf("%d", &day);

    printf("ʱ��Σ�24Сʱ�ƣ���\n");
    printf("��ԤԼʱ��Ϊ����һ��������15��00-21��00������������6��00-21��00\n");
    printf("ע�⣺����һ��������17��00-20��00Ϊ�̹���Э�ʱ�䣬����ԤԼ��\n");
    scanf("%d", &hour);
    if((day == 1 || day == 3 || day == 5) && (hour >= 17 && hour < 20))
    {
        printf("��ʱ���Ϊ�̹��ʱ�䣬����ԤԼ\n");
        return ;
    }
    if (((day >= 1 && day <= 5) && (hour >= 15 && hour <= 20)) ||
        ((day == 6 || day == 7)&& (hour >= 9 && hour <= 20))) {
        printf("����/ѧ�ţ�");
        scanf("%s", id);
        printf("������");
        scanf("%s", name);
        printf("��ϵ�绰��");
        scanf("%s", phoneNumber);

    // ����Ƿ��ڹ涨��ԤԼʱ�䷶Χ��


        // ����Ƿ��Ѵ�����ͬ��ԤԼ��¼
        for (int i = 0; i < numReservations; i++) {
            if (reservations[i].day == day && reservations[i].hour == hour &&
                strcmp(reservations[i].phone, phoneNumber) == 0 && strcmp(reservations[i].name, name) == 0 && strcmp(reservations[i].id, id) == 0) {
                printf("ͬһ�˲�����ͬһʱ����ٴ�ԤԼ��\n");
                return; // ԤԼʧ�ܣ�����
            }
        }

        // ��鵥�������ڵ���ʱ����ڵ�Ԥ�������Ƿ񳬹�4��
        int reservationCount = 0;

        for (int i = 0; i < numReservations; i++) {
            if (reservations[i].courtNumber == courtNumber && reservations[i].day == day && reservations[i].hour == hour) {
                reservationCount++;

                if (reservationCount >= MAX_RESERVATIONS) {
                    printf("�ó����ڸ�ʱ�����Ԥ��������������ѡ������ʱ��λ򳡵ء�\n");
                    return; // ԤԼʧ�ܣ�����
                }
            }
        }

        // ����ԤԼ��Ϣ
        reservations[numReservations].courtNumber = courtNumber;
        reservations[numReservations].day = day;
        reservations[numReservations].hour = hour;
        strcpy(reservations[numReservations].id, id);
        strcpy(reservations[numReservations].name, name);
        strcpy(reservations[numReservations].phone, phoneNumber);

        numReservations++;


        saveReservationsToFile();//���µ�����ȫ��д�롣
        printf("ԤԼ�ɹ���\n");
        return; // ԤԼ�ɹ�������
    }
    else {
        printf("����Ԥ��ʱ���ڣ�����Ԥ����\n");
        return; // ԤԼʧ�ܣ�����
    }
}


int main() {
    // ��ʼ��������Ϣ
    for (int i = 0; i < MAX_COURTS; i++) {
        courts[i].courtNumber = i + 1;
        courts[i].availableCount = 4;
        courts[i].reservedCount = 0;
    }

    // ���ļ�����ԤԼ��¼���ļ�������ת�浽�ṹ���
    //�����ڹ����еı��溯��ʹ�ýṹ�������ת���ļ��б��档
    loadReservationsFromFile();

    int choice;

    do {
        printf("\n��ӭʹ��ԤԼϵͳ��\n");
        printf("1. ��ʾ������Ϣ\n");
        printf("2. ��ʾԤԼ��Ϣ\n");
        printf("3. ��ѯ����ԤԼ��Ϣ\n");
        printf("4. ��ѯ�ֻ���ԤԼ��Ϣ\n");
        printf("5. ȡ��ԤԼ\n");
        printf("6. ���ԤԼ\n");
        printf("0. �˳�\n");
        printf("����������ѡ��");
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
                printf("��лʹ��ԤԼϵͳ���ټ���\n");
                break;
            default:
                printf("��Ч��ѡ�����������롣\n");
                break;
        }
    } while (choice != 0);

    return 0;
}
