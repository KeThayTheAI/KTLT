#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "models.h"
#include "utils.h"
#include "transaction.h"
#include "budget.h"
#include "file_io.h"

void themNganSachVaoList(NganSach ns)
{
    if (listNS.size == listNS.capacity)
    {
        int newCapacity = (listNS.capacity == 0) ? 5 : listNS.capacity * 2;
        NganSach *newData = (NganSach *)realloc(listNS.data, newCapacity * sizeof(NganSach));
        if (newData == NULL)
        {
            printf("Loi: Khong du bo nho de them ngan sach!\n");
            return;
        }
        listNS.data = newData;
        listNS.capacity = newCapacity;
    }
    listNS.data[listNS.size] = ns;
    listNS.size++;
}

int timViTriNganSach(char *danhMuc, int thang, int nam)
{
    for (int i = 0; i < listNS.size; i++)
    {
        if (strcmp(listNS.data[i].danhMuc, danhMuc) == 0 &&
            listNS.data[i].thang == thang &&
            listNS.data[i].nam == nam)
        {
            return i;
        }
    }
    return -1;
}

double tinhTongChiDanhMucTheoThang(char *danhMuc, int thang, int nam)
{
    double tongChi = 0;
    for (int i = 0; i < listGD.size; i++)
    {
        int d, m, y;
        if (listGD.data[i].loai == 2 &&
            strcmp(listGD.data[i].danhMuc, danhMuc) == 0 &&
            tachNgay(listGD.data[i].ngay, &d, &m, &y) &&
            m == thang && y == nam)
        {
            tongChi += listGD.data[i].soTien;
        }
    }
    return tongChi;
}

void canhBaoVuotNganSach(GiaoDich gd)
{
    int d, m, y;
    int viTriNS;
    double tongChi;

    if (gd.loai != 2 || !tachNgay(gd.ngay, &d, &m, &y))
    {
        return;
    }

    viTriNS = timViTriNganSach(gd.danhMuc, m, y);
    if (viTriNS == -1)
    {
        return;
    }

    tongChi = tinhTongChiDanhMucTheoThang(gd.danhMuc, m, y);
    if (tongChi >= listNS.data[viTriNS].hanMuc)
    {
        printf("\033[31m");
        printf("CANH BAO: BAN DA TIEU VUOT NGAN SACH THANG NAY\n");
        printf("Danh muc: %s | Thang: %d/%d\n", gd.danhMuc, m, y);
        printf("Han muc cho phep: %.2f | Tong da chi: %.2f | Vuot: %.2f\n",
               listNS.data[viTriNS].hanMuc, tongChi, tongChi - listNS.data[viTriNS].hanMuc);
        printf("\033[0m");
    }
}

void inCanhBaoVuotNganSachTheoKy(int locTheoThang, int thang, int nam)
{
    int coVuot = 0;

    printf("\nCAC MUC VUOT NGAN SACH\n");
    for (int i = 0; i < listNS.size; i++)
    {
        if (locTheoThang && (listNS.data[i].thang != thang || listNS.data[i].nam != nam))
        {
            continue;
        }

        double tongChi = tinhTongChiDanhMucTheoThang(listNS.data[i].danhMuc, listNS.data[i].thang, listNS.data[i].nam);
        if (tongChi > listNS.data[i].hanMuc)
        {
            printf("\033[31m");
            printf("- %s thang %d/%d: da chi %.2f, han muc %.2f, vuot %.2f\n",
                   listNS.data[i].danhMuc,
                   listNS.data[i].thang,
                   listNS.data[i].nam,
                   tongChi,
                   listNS.data[i].hanMuc,
                   tongChi - listNS.data[i].hanMuc);
            printf("\033[0m");
            coVuot = 1;
        }
    }

    if (!coVuot)
    {
        printf("Khong co danh muc nao vuot ngan sach.\n");
    }
}

void thietLapNganSach(void)
{
    NganSach ns;
    printf("\nTHIET LAP NGAN SACH\n");
    chonDanhMucChi(ns.danhMuc);

    do
    {
        printf("Nhap thang (1-12): ");
        scanf("%d", &ns.thang);
        if (ns.thang < 1 || ns.thang > 12)
        {
            printf("Thang khong hop le.\n");
        }
    } while (ns.thang < 1 || ns.thang > 12);

    do
    {
        printf("Nhap nam: ");
        scanf("%d", &ns.nam);
        if (ns.nam < 1900 || ns.nam > 2100)
        {
            printf("Nam khong hop le.\n");
        }
    } while (ns.nam < 1900 || ns.nam > 2100);

    do
    {
        printf("Nhap han muc toi da cho '%s' (VND): ", ns.danhMuc);
        scanf("%lf", &ns.hanMuc);
        if (ns.hanMuc < 0)
        {
            printf("Han muc khong duoc am.\n");
        }
    } while (ns.hanMuc < 0);
    xoaBoNhoDem();

    int tonTai = 0;
    for (int i = 0; i < listNS.size; i++)
    {
        if (strcmp(listNS.data[i].danhMuc, ns.danhMuc) == 0 && listNS.data[i].thang == ns.thang && listNS.data[i].nam == ns.nam)
        {
            listNS.data[i].hanMuc = ns.hanMuc;
            tonTai = 1;
            printf("Ngan sach cho danh muc nay nay da ton tai. Da cap nhat han muc moi.\n");
            break;
        }
    }

    if (!tonTai)
    {
        themNganSachVaoList(ns);
    }

    luuFileNganSach();
    printf("Thiet lap ngan sach cho '%s' thang %d/%d thanh cong\n", ns.danhMuc, ns.thang, ns.nam);
}

void xemNganSach(void)
{
    if (listNS.size == 0)
    {
        printf("Chua co ngan sach nao.\n");
        return;
    }

    printf("\nDANH SACH NGAN SACH\n");
    printf("%-5s %-20s %-10s %-10s %-15s\n", "STT", "Danh muc", "Thang", "Nam", "Han muc");
    for (int i = 0; i < listNS.size; i++)
    {
        printf("%-5d %-20s %-10d %-10d %-15.2f\n",
               i + 1,
               listNS.data[i].danhMuc,
               listNS.data[i].thang,
               listNS.data[i].nam,
               listNS.data[i].hanMuc);
    }
}

void suaNganSach(void)
{
    int stt;

    if (listNS.size == 0)
    {
        printf("Chua co ngan sach de sua.\n");
        return;
    }

    xemNganSach();
    printf("Nhap STT ngan sach can sua: ");
    scanf("%d", &stt);
    xoaBoNhoDem();

    if (stt < 1 || stt > listNS.size)
    {
        printf("STT khong hop le.\n");
        return;
    }

    stt--;
    
    int suaDanhMuc;

    do {
        printf("Danh muc hien tai: %s\n", listNS.data[stt].danhMuc);
        printf("Ban co muon sua danh muc khong?\n");
        printf("0. Giu nguyen\n");
        printf("1. Chon lai danh muc chi tieu\n");
        printf("Nhap lua chon: ");
        scanf("%d", &suaDanhMuc);
        xoaBoNhoDem();

        if (suaDanhMuc == 0) {
            break;
        }
        else if (suaDanhMuc == 1) {
            chonDanhMucChi(listNS.data[stt].danhMuc);
            break;
        }
        else {
            printf("Lua chon khong hop le. Vui long nhap 0 hoac 1.\n");
        }
    } while (1);

    int thangMoi;
    do
    {
        printf("Thang hien tai: %d. Nhap thang moi hoac 0 de giu nguyen: ",
               listNS.data[stt].thang);
        scanf("%d", &thangMoi);
        xoaBoNhoDem();

        if (thangMoi != 0 && (thangMoi < 1 || thangMoi > 12))
        {
            printf("Thang khong hop le. Vui long nhap tu 1 den 12, hoac 0 de giu nguyen.\n");
        }
    } while (thangMoi != 0 && (thangMoi < 1 || thangMoi > 12));

    if (thangMoi != 0)
    {
        listNS.data[stt].thang = thangMoi;
    }

    int namMoi;
    do
    {
        printf("Nam hien tai: %d. Nhap nam moi hoac 0 de giu nguyen: ", listNS.data[stt].nam);
        scanf("%d", &namMoi);
        xoaBoNhoDem();

        if (namMoi != 0 && (namMoi < 1900 || namMoi > 2100))
        {
            printf("Nam khong hop le. Vui long nhap tu 1900 den 2100, hoac 0 de giu nguyen.\n");
        }
    } while (namMoi != 0 && (namMoi < 1900 || namMoi > 2100));

    if (namMoi != 0)
    {
        listNS.data[stt].nam = namMoi;
    }

    double hanMucMoi;

    do
    {
        printf("Han muc hien tai: %.2f. Nhap han muc moi hoac 0 de giu nguyen: ", listNS.data[stt].hanMuc);
        scanf("%lf", &hanMucMoi);
        xoaBoNhoDem();

        if (hanMucMoi < 0)
        {
            printf("Han muc khong duoc am. Vui long nhap lai.\n");
        }
    } while (hanMucMoi < 0);

    if (hanMucMoi > 0)
    {
        listNS.data[stt].hanMuc = hanMucMoi;
    }

    luuFileNganSach();
    printf("Da sua ngan sach.\n");
}

void xoaNganSach(void)
{
    int stt;

    if (listNS.size == 0)
    {
        printf("Chua co ngan sach de xoa.\n");
        return;
    }

    xemNganSach();
    printf("Nhap STT ngan sach can xoa: ");
    scanf("%d", &stt);
    xoaBoNhoDem();

    if (stt < 1 || stt > listNS.size)
    {
        printf("STT khong hop le.\n");
        return;
    }

    stt--;
    for (int i = stt; i < listNS.size - 1; i++)
    {
        listNS.data[i] = listNS.data[i + 1];
    }
    listNS.size--;
    luuFileNganSach();
    printf("Da xoa ngan sach.\n");
}

void quanLyNganSach(void)
{
    int luaChon;
    do
    {
        printf("\nQUAN LY NGAN SACH\n");
        printf("1. Xem danh sach ngan sach\n");
        printf("2. Them ngan sach\n");
        printf("3. Sua ngan sach\n");
        printf("4. Xoa ngan sach\n");
        printf("5. Kiem tra canh bao vuot ngan sach\n");
        printf("0. Quay lai\n");
        printf("Nhap lua chon: ");
        scanf("%d", &luaChon);
        xoaBoNhoDem();

        switch (luaChon)
        {
        case 1:
            xemNganSach();
            break;
        case 2:
            thietLapNganSach();
            break;
        case 3:
            suaNganSach();
            break;
        case 4:
            xoaNganSach();
            break;
        case 5:
            inCanhBaoVuotNganSachTheoKy(0, 0, 0);
            break;
        case 0:
            break;
        default:
            printf("Lua chon khong hop le.\n");
        }
    } while (luaChon != 0);
}

void giaiPhongNganSach(void)
{
    free(listNS.data);
    listNS.data = NULL;
    listNS.size = 0;
    listNS.capacity = 0;
}
