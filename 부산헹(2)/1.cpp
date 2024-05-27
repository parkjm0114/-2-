#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>

//�Ķ����
//���� ����
#define LEN_MIN 15
#define LEN_MAX 50
//Ȯ��
#define PROB_MIN 10
#define PROB_MAX 90
//������ ü��
#define STM_MIN  0
#define STM_MAX  5
//��׷� ����
#define AGGRO_MIN  0
#define AGGRO_MAX  5
//������ �̵� ����
#define MOVE_LEFT  1
#define MOVE_STAY  0
// �����ǰ��ݴ��
#define ATK_NONE  0
#define ATK_CITIZEN  1
#define ATK_DONGSEOK  2
// �������ൿ
#define ACTION_REST  0
#define ACTION_PROVOKE  1
#define ACTION_PULL  2


int main(void) {

    int LEN; //���� ����
    int PROB; //Ȯ��
    int STM; //������ ü��
    int C_AGGRO = 1; //�ù� ��׷�
    int M_AGGRO = 1; //������ ��׷�
    int MOVE; //������ �̵�
    int C, Z, M; // �ù�, ����
    int i;
    int Z_turn = 0; // Z�� 2�ϸ��� �����̱� ���� ����

    while (1) {
        //���� ���� �Է� �� ���� ����
        printf("train length(15~50) >> ");
        scanf_s("%d", &LEN);

        if (LEN >= LEN_MIN && LEN <= LEN_MAX) {
            break;
        }
    }
    while (1) {
        //������ ü�� �Է� �� ���� ����
        printf("madongseokstamina(0~5)>> ");
        scanf_s("%d", &STM);

        if (STM >= STM_MIN && STM <= STM_MAX) {
            break;
        }
    }
    while (1) {
        //Ȯ�� �Է� �� ���� ����
        printf("percentile probability 'p'(10~90) >> ");
        scanf_s("%d", &PROB);

        if (PROB >= PROB_MIN && PROB <= PROB_MAX) {
            break;
        }
    }
    
    // ���� ����
    srand((unsigned int)time(NULL));

    // C�� Z�� �ʱ� ���� ����
    C = LEN - 6;
    Z = LEN - 3;
    M = LEN - 2;

    // ���� �����
    for (i = 0; i < LEN; i++) {
        printf("#");
    }
    printf("\n");
    printf("#");
    for (i = 1; i < LEN - 1; i++) {
        if (i == C)
            printf("C");
        else if (i == Z)
            printf("Z");
        else if (i == M)
            printf("M");
        else
            printf(" ");
    }
    printf("#\n");
    for (i = 0; i < LEN; i++) {
        printf("#");
    }
    printf("\n\n");
    Sleep(4000);

    // �ݺ���
    while (1) {

        // Z�� C �� ĭ�� �����ϸ� ���� ����
        if (Z == C + 1) {
            printf("GAME OVER!\nCitizen(s) has(have) been attacked by a zombie\n");
            break;
        }

        // 0���� 100 ������ ������ ����
        int r1 = rand() % 101;
        int r2 = rand() % 101;

        // �ù� �̵�
        if (r1 <= (100 - PROB)) {
            C--;
        }
        //�����̵�
        if (Z_turn % 2 == 0) {
            if (C_AGGRO >= M_AGGRO) {
                Z--;
            }
            else {
                Z++;
            }
        }

        // ���� ���� ���
        for (i = 0; i < LEN; i++) {
            printf("#");
        }
        printf("\n");
        printf("#");
        for (i = 1; i < LEN - 1; i++) {
            if (i == C)
                printf("C");
            else if (i == Z)
                printf("Z");
            else if (i == M)
                printf("M");
            else
                printf(" ");
        }
        printf("#\n");
        for (i = 0; i < LEN; i++) {
            printf("#");
        }
        printf("\n\n");

        // �ù� ���� ���
        if (r1 <= (100 - PROB)) {
            if (C_AGGRO < AGGRO_MAX && C_AGGRO > AGGRO_MIN) {
                C_AGGRO++; 
            }
            printf("citizen: %d -> %d (aggro: %d -> %d)\n", C + 1, C, C_AGGRO - 1, C_AGGRO);
        }
        else {
            if (C_AGGRO < AGGRO_MAX && C_AGGRO > AGGRO_MIN) {
                C_AGGRO--;   
            }
            printf("citizen: stay %d (aggro: %d -> %d)\n", C, C_AGGRO + 1, C_AGGRO);
        }

        // ���� ���� ���
        if (Z_turn % 2 == 0) {
            if (C_AGGRO >= M_AGGRO) {
                printf("zombie: %d -> %d\n", Z + 1, Z);
            }
            else{
                printf("zombie: %d -> %d\n", Z - 1, Z);
            }
            if (M == C + 1) {
                printf("zombie: stay %d\n", Z);
            }
            else if (Z == M + 1) {
                printf("zombie: stay %d\n", Z);
            }
        }

        if (Z_turn % 2 == 1) {
            printf("zombie: stay %d (cannot move)\n", Z);
        }
        printf("\n");

        
        while (1) {
            printf("madongseokmove(0:stay, 1:left)>>");
            scanf_s("%d", &MOVE);

            if (MOVE == MOVE_LEFT || MOVE == MOVE_STAY) {
                break;
            }
        }
        //������ �̵�
        if (MOVE == MOVE_LEFT) {
            M--;
        }

        for (i = 0; i < LEN; i++) {
            printf("#");
        }
        printf("\n");
        printf("#");
        for (i = 1; i < LEN - 1; i++) {
            if (i == C)
                printf("C");
            else if (i == Z)
                printf("Z");
            else if (i == M)
                printf("M");
            else
                printf(" ");
        }
        printf("#\n");
        for (i = 0; i < LEN; i++) {
            printf("#");
        }
        printf("\n\n");

        if (MOVE == MOVE_LEFT) {
            if (M_AGGRO < AGGRO_MAX && M_AGGRO > AGGRO_MIN) {
                M_AGGRO++;
            }
            printf("madongseok: %d -> %d (aggro: %d -> %d)\n", M + 1, M, M_AGGRO - 1 ,M_AGGRO);
        }
        else if (MOVE == MOVE_STAY) {
            if (M_AGGRO < AGGRO_MAX && M_AGGRO > AGGRO_MIN) {
                M_AGGRO--;
            }
            printf("madongseok: stay %d(aggro: %d -> %d, stamina: %d)\n", M, M_AGGRO + 1, M_AGGRO, STM);
        }

        //�ൿ
        
        // C�� ���ʳ�(1����)�� �����ϸ� ���� ����
        if (C == 1) {
            printf("SUCCESS!\ncitizen(s) escaped to the next train\n");
            break;
        }
        else {
            printf("citizen does nothing.");
        }
        
        
        // �� ����
        Z_turn++;
    }
}