#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "models.h"
#include "utils.h"
#include "transaction.h"
#include "budget.h"
#include "file_io.h"
#include "report.h"

ListGiaoDich listGD = {NULL, 0, 0};
ListNganSach listNS = {NULL, 0, 0};
long long soDu = 0;
int main(void)
{
    docFile();
    docFileNganSach();

    int luaChon;
    do
    {
        printf("\nQUAN LY CHI TIEU CA NHAN\n");
        printf("So du hien tai: %lld\n", soDu);
        printf("1. Quan ly giao dich\n");
        printf("2. Bao cao thong ke\n");
        printf("3. Quan ly ngan sach\n");
        printf("0. Thoat chuong trinh\n");
        printf("Nhap lua chon: ");
        scanf("%d", &luaChon);
        xoaBoNhoDem();

        switch (luaChon)
        {
        case 1:
            quanLyGiaoDich();
            break;
        case 2:
            thongKe();
            break;
        case 3:
            quanLyNganSach();
            break;
        case 0:
            luuFile();
            luuFileNganSach();
            giaiPhongGiaoDich();
            giaiPhongNganSach();
            printf("Dang thoat chuong trinh. Du lieu da duoc luu\n");
            break;
        default:
            printf("Lua chon khong hop le. Vui long thu lai\n");
        }
    } while (luaChon != 0);

    return 0;
}
