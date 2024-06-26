#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//파라미터
#define LEN_MIN 15      //기차 길이
#define LEN_MAX 50
#define PROB_MIN 10     //확률
#define PROB_MAX 90
#define STM_MIN  0      //마동석 체력 
#define STM_MAX  5
#define AGGRO_MIN  0    //어그로 범위
#define AGGRO_MAX  5

//마동석 이동 방향
#define MOVE_LEFT  1
#define MOVE_STAY  0

// 좀비의공격대상
#define ATK_NONE  0
#define ATK_CITIZEN  1
#define ATK_DONGSEOK  2

// 마동석행동
#define ACTION_REST  0
#define ACTION_PROVOKE  1
#define ACTION_PULL  2

int main(void) {

    int LEN;            //기차 길이
    int PROB;           //확률
    int STM;        //마동석 체력
    int C_AGGRO = 1;    //시민 어그로
    int M_AGGRO = 1;    //마동석 어그로
    int MOVE;           //마동석 이동
    int ATK;            //좀비공격대상
    int ACTION;     //마동석 행동
    int C, Z, M;        // 시민, 좀비, 마동석
    int i;
    int Z_turn = 0;     // Z를 2턴마다 움직이기 위한 변수
    
    //기차 길이 입력 및 범위 설정
    while (1) {
        printf("train length(15~50) >> ");
        scanf_s("%d", &LEN);
        if (LEN >= LEN_MIN && LEN <= LEN_MAX) {
            break;
        }
    }
    //마동석 체력 입력 및 범위 설정
    while (1) {
        printf("madongseokstamina(0~5)>> ");
        scanf_s("%d", &STM);
        if (STM >= STM_MIN && STM <= STM_MAX) {
            break;
        }
    }
    //확률 입력 및 범위 설정
    while (1) {
        printf("percentile probability 'p'(10~90) >> ");
        scanf_s("%d", &PROB);
        if (PROB >= PROB_MIN && PROB <= PROB_MAX) {
            break;
        }
    }
    
    // 난수 설정
    srand((unsigned int)time(NULL));

    // C와 Z의 초기 상태 설정
    C = LEN - 6;
    Z = LEN - 3;
    M = LEN - 2;

    // 기차 만들기
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

    while (1) {

        // 0부터 100 사이의 난수를 생성
        int r1 = rand() % 101;
        int r2 = rand() % 101;

        // 시민 이동
        if (r1 <= (100 - PROB)) {
            C--;
        }
        //좀비이동
        if (Z_turn % 2 == 0) {
            if (C_AGGRO >= M_AGGRO) {
                Z--;
            }
            else {
                Z++;
            }
            if (Z !== C + 1 || M !== Z + 1) {
                continue;
            }
        }

        // 열차 상태 출력
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

        // 시민 상태 출력
        
        if (r1 <= (100 - PROB)) {
            printf("citizen: %d -> %d (aggro: %d -> %d)\n", C + 1, C, C_AGGRO, C_AGGRO + 1);
            C_AGGRO++;
        }
        else {
            printf("citizen: stay %d (aggro: %d -> %d)\n", C, C_AGGRO, C_AGGRO - 1);
            C_AGGRO--;
        }

        // 좀비 상태 출력
        if (Z--) {
            printf("zombie: %d -> %d\n", Z + 1, Z);
        }
        else {
            printf("zombie: %d -> %d\n", Z - 1, Z);
        }
        if (Z != C + 1 || M != Z + 1) {
            printf("zombie: stay %d\n", Z);
        }
        if (ACTION == ACTION_PULL && r2 <= (100 - PROB)) {
            printf("zombie: stay %d\n", Z);
        }}
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

        //마동석 이동
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
            printf("madongseok: %d -> %d (aggro: %d -> %d, stamina: %d)\n", M + 1, M, M_AGGRO, M_AGGRO + 1, STM);
            M_AGGRO++;
        }
        else {
            printf("madongseok: stay %d(aggro: %d -> %d, stamina: %d)\n", M, M_AGGRO, M_AGGRO - 1, STM);
            M_AGGRO--;
        }

        //행동
        
        // C행동
        if (C == 1) {
            printf("SUCCESS!\ncitizen(s) escaped to the next train\n");
            break;
        }
        else {
            printf("citizen does nothing.\n");
        }

        // Z 행동
        if (Z == C + 1) {
            if (C_AGGRO > M_AGGRO) {
                printf("GAME OVER!\nCitizen(s) has(have) been attacked by a zombie\n");
                break;
            }
            else {
                printf("zombie attacked nobody.\n");
            }
        }
        else if (M == Z + 1) {
            if (C_AGGRO <= M_AGGRO) {
                printf("Zomibeattacked madongseok(aggro: %d vs. %d, madongseokstamina: %d -> %d)\n", C_AGGRO, M_AGGRO, STM, STM - 1);
                STM--;
            }
            else {
                printf("zombie attacked nobody.\n");
            }
        }
        //둘다 인접한경우
        else if (Z == C + 1 && M == Z + 1) {
            if (C_AGGRO > M_AGGRO) {
                printf("GAME OVER!\nCitizen(s) has(have) been attacked by a zombie\n");
                break;
            }
            else {
                printf("Zomibeattacked madongseok(aggro: %d vs. %d, madongseokstamina: %d -> %d)\n", C_AGGRO, M_AGGRO, STM, STM - 1);
                STM--; 
            }
        }
        if (STM == STM_MIN) {
            printf("GAME OEVER! citizen dead...\n");
            break;
        }
        

        while (1) {
            
            if (M == Z + 1) {
                printf("madongseokaction(0.rest, 1.provoke, 2. pull)>> ");
                scanf_s("%d", &ACTION);
            }
            else {
                printf("madongseokaction(0.rest, 1.provoke)>>");
                scanf_s("%d", &ACTION);
            }
            
            if (ACTION == ACTION_REST) {
                M_AGGRO--;
                STM++;
            }
            else if (ACTION == ACTION_PROVOKE) {
                M_AGGRO = AGGRO_MAX;
            }
            else if (ACTION == ACTION_PULL) {
                M_AGGRO += 2;
                STM--;
                if (r2 <= (100 - PROB)) {
                    printf("madongseokpulled zombie... Next turn, it can't move\n");
                }
                else {
                    printf("madongseokfailed to pull zombie\n");
                }
            }
            if (ACTION == ACTION_REST || ACTION == ACTION_PROVOKE || ACTION == ACTION_PULL) {
                break;
            }
        }
        // 턴 증가
        Z_turn++;
    }
}
