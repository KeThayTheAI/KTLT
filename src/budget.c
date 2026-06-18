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
    printf("DANH MUC CHI TIEU\n");
    printf(" 1. An uong             7. Giao duc\n");
    printf(" 2. Chi tieu hang ngay  8. Tien dien\n");
    printf(" 3. Quan ao             9. Di lai\n");
    printf(" 4. My pham            10. Tien nha\n");
    printf(" 5. Phi giao luu       11. Di choi\n");
    printf(" 6. Y te               12. Shopee\n");
    printf(" 13. Muc khac (Tu nhap tu ban phim)\n");
    printf("Chon danh muc de dat ngan sach: ");

    int chonChi;
    scanf("%d", &chonChi);
    xoaBoNhoDem();

    switch (chonChi)
    {
    case 1:
        strcpy(ns.danhMuc, "An uong");
        break;
    case 2:
        strcpy(ns.danhMuc, "Chi tieu hang ngay");
        break;
    case 3:
        strcpy(ns.danhMuc, "Quan ao");
        break;
    case 4:
        strcpy(ns.danhMuc, "My pham");
        break;
    case 5:
        strcpy(ns.danhMuc, "Phi giao luu");
        break;
    case 6:
        strcpy(ns.danhMuc, "Y te");
        break;
    case 7:
        strcpy(ns.danhMuc, "Giao duc");
        break;
    case 8:
        strcpy(ns.danhMuc, "Tien dien");
        break;
    case 9:
        strcpy(ns.danhMuc, "Di lai");
        break;
    case 10:
        strcpy(ns.danhMuc, "Tien nha");
        break;
    case 11:
        strcpy(ns.danhMuc, "Di choi");
        break;
    case 12:
        strcpy(ns.danhMuc, "Shopee");
        break;
    case 13:
        printf("Nhap ten danh muc khac: ");
        fgets(ns.danhMuc, sizeof(ns.danhMuc), stdin);
        xoaXuongDong(ns.danhMuc);
        break;
    default:
        strcpy(ns.danhMuc, "Khong xac dinh");
        break;
    }

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
    char buffer[80];

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
    printf("Danh muc hien tai: %s. Nhap danh muc moi hoac Enter de giu nguyen: ", listNS.data[stt].danhMuc);
    fgets(buffer, sizeof(buffer), stdin);
    xoaXuongDong(buffer);
    if (strlen(buffer) > 0)
    {
        strncpy(listNS.data[stt].danhMuc, buffer, sizeof(listNS.data[stt].danhMuc) - 1);
        listNS.data[stt].danhMuc[sizeof(listNS.data[stt].danhMuc) - 1] = '\0';
    }

    printf("Thang hien tai: %d. Nhap thang moi hoac 0 de giu nguyen: ", listNS.data[stt].thang);
    int thangMoi;
    scanf("%d", &thangMoi);
    xoaBoNhoDem();
    if (thangMoi >= 1 && thangMoi <= 12)
    {
        listNS.data[stt].thang = thangMoi;
    }

    printf("Nam hien tai: %d. Nhap nam moi hoac 0 de giu nguyen: ", listNS.data[stt].nam);
    int namMoi;
    scanf("%d", &namMoi);
    xoaBoNhoDem();
    if (namMoi >= 1900 && namMoi <= 2100)
    {
        listNS.data[stt].nam = namMoi;
    }

    printf("Han muc hien tai: %.2f. Nhap han muc moi hoac -1 de giu nguyen: ", listNS.data[stt].hanMuc);
    double hanMucMoi;
    scanf("%lf", &hanMucMoi);
    xoaBoNhoDem();
    if (hanMucMoi >= 0)
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
        printf("2. Them hoac cap nhat ngan sach\n");
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
