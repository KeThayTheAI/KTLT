#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "report.h"
#include "models.h"
#include "utils.h"
#include "transaction.h"
#include "budget.h"
#include "file_io.h"

void themThongKeDanhMuc(ListThongKe *tk, char *danhMuc, long long soTien)
{
    for (int i = 0; i < tk->size; i++)
    {
        if (strcmp(tk->data[i].danhMuc, danhMuc) == 0)
        {
            tk->data[i].tongTien += soTien;
            return;
        }
    }

    if (tk->size == tk->capacity)
    {
        int newCapacity = (tk->capacity == 0) ? 5 : tk->capacity * 2;
        ThongKeDanhMuc *newData = (ThongKeDanhMuc *)realloc(tk->data, newCapacity * sizeof(ThongKeDanhMuc));
        if (newData == NULL)
        {
            printf("Loi: Khong du bo nho de thong ke danh muc!\n");
            return;
        }
        tk->data = newData;
        tk->capacity = newCapacity;
    }

    strncpy(tk->data[tk->size].danhMuc, danhMuc, sizeof(tk->data[tk->size].danhMuc) - 1);
    tk->data[tk->size].danhMuc[sizeof(tk->data[tk->size].danhMuc) - 1] = '\0';
    tk->data[tk->size].tongTien = soTien;
    tk->size++;
}


void inThongKeDanhMuc(char *tieuDe, ListThongKe *tk, long long tongTien)
{
    printf("%s\n", tieuDe);

    if (tk->size == 0)
    {
        printf("  Khong co du lieu trong ky.\n");
        return;
    }

    for (int i = 0; i < tk->size; i++)
    {
        double tyLe = (tongTien > 0) ? tk->data[i].tongTien * 100.0 / tongTien : 0;
        printf("  - %-20s: %lld (%.2f%%) \n", tk->data[i].danhMuc, tk->data[i].tongTien, tyLe);
    }
}

int giaoDichThuocKyThongKe(GiaoDich gd, int locTheoThang, int thang, int nam)
{
    int d, m, y;
    if (!locTheoThang)
    {
        return 1;
    }
    if (!tachNgay(gd.ngay, &d, &m, &y))
    {
        return 0;
    }
    return m == thang && y == nam;
}

void thongKe(void)
{
    if (listGD.size == 0)
    {
        printf("Khong co du lieu de thong ke!\n");
        return;
    }

    long long tongThu = 0, tongChi = 0;
    int luaChon, thang = 0, nam = 0, locTheoThang = 0;
    ListThongKe tkThu = {NULL, 0, 0};
    ListThongKe tkChi = {NULL, 0, 0};

    printf("\nTHONG KE GIAO DICH\n");
    printf("1. Thong ke theo thang/nam\n");
    printf("2. Thong ke toan bo giao dich\n");
    printf("Nhap lua chon: ");
    scanf("%d", &luaChon);
    xoaBoNhoDem();

    if (luaChon == 1)
    {
        locTheoThang = 1;
        printf("Nhap thang (1-12): ");
        scanf("%d", &thang);
        printf("Nhap nam: ");
        scanf("%d", &nam);
        xoaBoNhoDem();

        if (thang < 1 || thang > 12 || nam < 1900 || nam > 2100)
        {
            printf("Thang/nam khong hop le.\n");
            return;
        }
    }
    else if (luaChon != 2)
    {
        printf("Lua chon khong hop le.\n");
        return;
    }

    for (int i = 0; i < listGD.size; i++)
    {
        if (!giaoDichThuocKyThongKe(listGD.data[i], locTheoThang, thang, nam))
        {
            continue;
        }

        if (listGD.data[i].loai == 1)
        {
            tongThu += listGD.data[i].soTien;
            themThongKeDanhMuc(&tkThu, listGD.data[i].danhMuc, listGD.data[i].soTien);
        }
        else if (listGD.data[i].loai == 2)
        {
            tongChi += listGD.data[i].soTien;
            themThongKeDanhMuc(&tkChi, listGD.data[i].danhMuc, listGD.data[i].soTien);
        }
    }

    if (locTheoThang)
    {
        printf("\nBAO CAO THANG %d/%d\n", thang, nam);
    }
    else
    {
        printf("\nBAO CAO TOAN BO GIAO DICH\n");
    }
    printf("Tong thu nhap : +%lld\n", tongThu);
    printf("Tong chi tieu : -%lld\n", tongChi);
    printf("So du trong ky: %lld\n", tongThu - tongChi);
    printf("\n");
    inThongKeDanhMuc("Chi tiet thu nhap theo danh muc:", &tkThu, tongThu);
    printf("\n");
    inThongKeDanhMuc("Chi tiet chi tieu theo danh muc:", &tkChi, tongChi);

    inCanhBaoVuotNganSachTheoKy(locTheoThang, thang, nam);
    free(tkThu.data);
    free(tkChi.data);
}
