#include <stdio.h>

#define BASE_FARE 12000.0
#define BASE_DISTANCE 2.0
#define EXTRA_RATE 4500.0
#define SURGE_MULTIPLIER 1.2

int main(void) {
    double distance_km;
    int is_surge;
    double base_fare;
    double total_fare;

    printf("Nhap quang duong (km): ");
    if (scanf("%lf", &distance_km) != 1) {
        printf("Loi: Quang duong khong hop le.\n");
        return 1;
    }

    if (distance_km <= 0.0) {
        printf("Loi: Quang duong phai lon hon 0 km.\n");
        return 1;
    }

    printf("Nhap trang thai phu phi (0 = binh thuong, 1 = cao diem/thoi tiet xau): ");
    if (scanf("%d", &is_surge) != 1) {
        printf("Loi: Trang thai phu phi khong hop le.\n");
        return 1;
    }

    if (is_surge != 0 && is_surge != 1) {
        printf("Loi: is_surge chi duoc nhan gia tri 0 hoac 1.\n");
        return 1;
    }

    if (distance_km <= BASE_DISTANCE) {
        base_fare = BASE_FARE;
    } else {
        double extra_distance = distance_km - BASE_DISTANCE;
        base_fare = BASE_FARE + extra_distance * EXTRA_RATE;
    }

    total_fare = base_fare;

    if (is_surge == 1) {
        total_fare *= SURGE_MULTIPLIER;
    }

    printf("\nKET QUA\n");
    printf("Quang duong: %.2f km\n", distance_km);
    printf("Trang thai surge: %d\n", is_surge);
    printf("Cuoc co ban: %.2f VND\n", base_fare);
    printf("Tong cuoc: %.2f VND\n", total_fare);

    return 0;
}

/*
Pseudocode:

BEGIN
    INPUT distance_km

    IF distance_km <= 0
        PRINT "Quang duong khong hop le"
        STOP
    END IF

    INPUT is_surge

    IF is_surge != 0 AND is_surge != 1
        PRINT "Trang thai phu phi khong hop le"
        STOP
    END IF

    IF distance_km <= 2.0
        base_fare = 12000
    ELSE
        base_fare = 12000 + (distance_km - 2.0) * 4500
    END IF

    total_fare = base_fare

    IF is_surge == 1
        total_fare = total_fare * 1.2
    END IF

    PRINT total_fare
END

Phan tich trade-off:

1. Legacy / Deeply Nested IF

- Nhieu tang if/else lam luong xu ly kho doc.
- Logic kiem tra loi bi tron voi logic tinh tien.
- Cong thuc phu phi co nguy co bi lap lai o nhieu nhanh.
- Khi thay doi gia cuoc hoac he so surge, de sua sot.
- Kha nang mo rong thap.

2. Refactored / Guard Clauses & Step-by-Step

- Du lieu sai duoc loai bo ngay tu dau.
- Tach rieng validation, tinh cuoc co ban va phu phi.
- Cong thuc tinh cuoc co ban chi nam o mot noi.
- Cac gia tri quan trong duoc dat thanh hang so.
- De kiem thu, bao tri va mo rong.

So sanh:

Legacy:
- Doc hieu: Kho
- Bao tri: Kho
- Code Duplication: Cao
- Mo rong: Kho

Refactored:
- Doc hieu: De
- Bao tri: De
- Code Duplication: Thap
- Mo rong: De

Lua chon:

Chon giai phap Refactored vi logic duoc chia thanh cac buoc ro rang.
Giai phap nay giam nested conditions, han che code duplication
va de thay doi khi business rules duoc cap nhat.
*/
