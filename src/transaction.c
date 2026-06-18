#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "models.h"
#include "utils.h"
#include "transaction.h"
#include "budget.h"
#include "file_io.h"

void themVaoCuoiDanhSach(GiaoDich gd)
{
    if (listGD.size == listGD.capacity)
    {
        int newCapacity = (listGD.capacity == 0) ? 10 : listGD.capacity * 2;
        GiaoDich *newData = (GiaoDich *)realloc(listGD.data, newCapacity * sizeof(GiaoDich));
        if (newData == NULL)
        {
            printf("Loi: Khong du bo nho de them giao dich!\n");
            return;
        }
        listGD.data = newData;
        listGD.capacity = newCapacity;
    }
    listGD.data[listGD.size] = gd;
    listGD.size++;
}

int layIdMoi(void)
{
    int maxId = 0;
    for (int i = 0; i < listGD.size; i++)
    {
        if (listGD.data[i].id > maxId)
        {
            maxId = listGD.data[i].id;
        }
    }
    return maxId + 1;
}

void sapXepTheoNgay(void)
{
    for (int i = 1; i < listGD.size; i++)
    {
        GiaoDich key = listGD.data[i];
        int j = i - 1;
        while (j >= 0 && (soSanhNgay(listGD.data[j].ngay, key.ngay) > 0 ||
                          (soSanhNgay(listGD.data[j].ngay, key.ngay) == 0 && listGD.data[j].id > key.id)))
        {
            listGD.data[j + 1] = listGD.data[j];
            j--;
        }
        listGD.data[j + 1] = key;
    }
}

int timViTriGiaoDichTheoId(int id)
{
    for (int i = 0; i < listGD.size; i++)
    {
        if (listGD.data[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

void tinhSoDu(void)
{
    soDu = 0.0;
    for (int i = 0; i < listGD.size; i++)
    {
        if (listGD.data[i].loai == 1)
            soDu += listGD.data[i].soTien;
        else if (listGD.data[i].loai == 2)
            soDu -= listGD.data[i].soTien;
    }
}

void themGiaoDich(void)
{
    GiaoDich gd;
    gd.id = layIdMoi();

    printf("\nNHAP GIAO DICH MOI\n");
    do
    {
        printf("Chon loai giao dich (1: Thu nhap, 2: Chi tieu): ");
        scanf("%d", &gd.loai);
        xoaBoNhoDem();
        if (gd.loai != 1 && gd.loai != 2)
        {
            printf("Loai giao dich khong hop le. Vui long nhap lai.\n");
        }
    } while (gd.loai != 1 && gd.loai != 2);

    do
    {
        printf("Nhap so tien: ");
        scanf("%lf", &gd.soTien);
        xoaBoNhoDem();
        if (gd.soTien <= 0)
        {
            printf("So tien phai lon hon 0.\n");
        }
    } while (gd.soTien <= 0);

    if (gd.loai == 1)
    {
        printf("\nDANH MUC THU NHAP\n");
        printf(" 1. Luong              3. Kinh doanh\n");
        printf(" 2. Thuong             4. Khac (Tu nhap)\n");
        printf("Chon danh muc (1-4): ");
        int chonThu;
        scanf("%d", &chonThu);
        xoaBoNhoDem();
        switch (chonThu)
        {
        case 1:
            strcpy(gd.danhMuc, "Luong");
            break;
        case 2:
            strcpy(gd.danhMuc, "Thuong");
            break;
        case 3:
            strcpy(gd.danhMuc, "Kinh doanh");
            break;
        case 4:
            printf("Nhap ten danh muc khac: ");
            fgets(gd.danhMuc, sizeof(gd.danhMuc), stdin);
            xoaXuongDong(gd.danhMuc);
            break;
        default:
            strcpy(gd.danhMuc, "Khac");
            break;
        }
    }
    else
    {
        printf("\nDANH MUC CHI TIEU\n");
        printf(" 1. An uong             7. Giao duc\n");
        printf(" 2. Chi tieu hang ngay  8. Tien dien\n");
        printf(" 3. Quan ao             9. Di lai\n");
        printf(" 4. My pham            10. Tien nha\n");
        printf(" 5. Phi giao luu       11. Di choi\n");
        printf(" 6. Y te               12. Shopee\n");
        printf(" 13. Muc khac (Tu nhap tu ban phim)\n");
        printf("Chon danh muc (1-13): ");
        int chonChi;
        scanf("%d", &chonChi);
        xoaBoNhoDem();
        switch (chonChi)
        {
        case 1:
            strcpy(gd.danhMuc, "An uong");
            break;
        case 2:
            strcpy(gd.danhMuc, "Chi tieu hang ngay");
            break;
        case 3:
            strcpy(gd.danhMuc, "Quan ao");
            break;
        case 4:
            strcpy(gd.danhMuc, "My pham");
            break;
        case 5:
            strcpy(gd.danhMuc, "Phi giao luu");
            break;
        case 6:
            strcpy(gd.danhMuc, "Y te");
            break;
        case 7:
            strcpy(gd.danhMuc, "Giao duc");
            break;
        case 8:
            strcpy(gd.danhMuc, "Tien dien");
            break;
        case 9:
            strcpy(gd.danhMuc, "Di lai");
            break;
        case 10:
            strcpy(gd.danhMuc, "Tien nha");
            break;
        case 11:
            strcpy(gd.danhMuc, "Di choi");
            break;
        case 12:
            strcpy(gd.danhMuc, "Shopee");
            break;
        case 13:
            printf("Nhap ten danh muc khac: ");
            fgets(gd.danhMuc, sizeof(gd.danhMuc), stdin);
            xoaXuongDong(gd.danhMuc);
            break;
        default:
            strcpy(gd.danhMuc, "Khong xac dinh");
            break;
        }
    }

    do
    {
        printf("Nhap ngay (DD/MM/YYYY): ");
        fgets(gd.ngay, sizeof(gd.ngay), stdin);
        xoaXuongDong(gd.ngay);
        if (!kiemTraNgayHopLe(gd.ngay))
        {
            printf("Loi: Ngay khong hop le hoac sai dinh dang. Vui long nhap lai\n");
        }
    } while (!kiemTraNgayHopLe(gd.ngay));

    printf("Nhap ghi chu: ");
    fgets(gd.ghiChu, sizeof(gd.ghiChu), stdin);
    xoaXuongDong(gd.ghiChu);

    themVaoCuoiDanhSach(gd);
    sapXepTheoNgay();
    tinhSoDu();
    luuFile();
    printf("Da them giao dich va luu vao file thanh cong\n");
    canhBaoVuotNganSach(gd);
}

void xemDanhSach(void)
{
    if (listGD.size == 0)
    {
        printf("Danh sach hien tai dang trong\n");
        return;
    }
    sapXepTheoNgay();
    printf("\nDANH SACH GIAO DICH\n");
    printf("%-5s %-10s %-15s %-20s %-15s %-20s\n", "ID", "Loai", "So Tien", "Danh Muc", "Ngay", "Ghi Chu");

    for (int i = 0; i < listGD.size; i++)
    {
        char loaiStr[10];
        strcpy(loaiStr, (listGD.data[i].loai == 1) ? "Thu" : "Chi");
        printf("%-5d %-10s %-15.2f %-20s %-15s %-20s\n",
               listGD.data[i].id, loaiStr, listGD.data[i].soTien,
               listGD.data[i].danhMuc, listGD.data[i].ngay, listGD.data[i].ghiChu);
    }
}

void suaGiaoDich(void)
{
    int idSua;
    int indexSua;
    char buffer[120];

    if (listGD.size == 0)
    {
        printf("Danh sach hien tai dang trong\n");
        return;
    }

    xemDanhSach();
    printf("\nNhap ID giao dich can sua: ");
    scanf("%d", &idSua);
    xoaBoNhoDem();

    indexSua = timViTriGiaoDichTheoId(idSua);
    if (indexSua == -1)
    {
        printf("Khong tim thay giao dich co ID %d.\n", idSua);
        return;
    }

    printf("Loai hien tai: %d (1: Thu, 2: Chi). Nhap loai moi hoac 0 de giu nguyen: ", listGD.data[indexSua].loai);
    int loaiMoi;
    scanf("%d", &loaiMoi);
    xoaBoNhoDem();
    if (loaiMoi == 1 || loaiMoi == 2)
    {
        listGD.data[indexSua].loai = loaiMoi;
    }

    printf("So tien hien tai: %.2f. Nhap so tien moi hoac 0 de giu nguyen: ", listGD.data[indexSua].soTien);
    double soTienMoi;
    scanf("%lf", &soTienMoi);
    xoaBoNhoDem();
    if (soTienMoi > 0)
    {
        listGD.data[indexSua].soTien = soTienMoi;
    }

    printf("Danh muc hien tai: %s. Nhap danh muc moi hoac Enter de giu nguyen: ", listGD.data[indexSua].danhMuc);
    fgets(buffer, sizeof(buffer), stdin);
    xoaXuongDong(buffer);
    if (strlen(buffer) > 0)
    {
        strncpy(listGD.data[indexSua].danhMuc, buffer, sizeof(listGD.data[indexSua].danhMuc) - 1);
        listGD.data[indexSua].danhMuc[sizeof(listGD.data[indexSua].danhMuc) - 1] = '\0';
    }

    do
    {
        printf("Ngay hien tai: %s. Nhap ngay moi (DD/MM/YYYY) hoac Enter de giu nguyen: ", listGD.data[indexSua].ngay);
        fgets(buffer, sizeof(buffer), stdin);
        xoaXuongDong(buffer);
        if (strlen(buffer) == 0)
        {
            break;
        }
        if (kiemTraNgayHopLe(buffer))
        {
            strncpy(listGD.data[indexSua].ngay, buffer, sizeof(listGD.data[indexSua].ngay) - 1);
            listGD.data[indexSua].ngay[sizeof(listGD.data[indexSua].ngay) - 1] = '\0';
            break;
        }
        printf("Ngay khong hop le. Vui long nhap lai.\n");
    } while (1);

    printf("Ghi chu hien tai: %s. Nhap ghi chu moi hoac Enter de giu nguyen: ", listGD.data[indexSua].ghiChu);
    fgets(buffer, sizeof(buffer), stdin);
    xoaXuongDong(buffer);
    if (strlen(buffer) > 0)
    {
        strncpy(listGD.data[indexSua].ghiChu, buffer, sizeof(listGD.data[indexSua].ghiChu) - 1);
        listGD.data[indexSua].ghiChu[sizeof(listGD.data[indexSua].ghiChu) - 1] = '\0';
    }

    sapXepTheoNgay();
    tinhSoDu();
    luuFile();
    printf("Da sua giao dich va cap nhat file\n");
    canhBaoVuotNganSach(listGD.data[timViTriGiaoDichTheoId(idSua)]);
}

void timKiem(void)
{
    if (listGD.size == 0)
    {
        printf("Danh sach trong\n");
        return;
    }

    int loaiTimKiem, chonMuc;
    char tuKhoa[50] = "";

    printf("\nTIM KIEM THEO DANH MUC\n");
    printf("1. Tim trong muc Thu nhap\n");
    printf("2. Tim trong muc Chi tieu\n");
    printf("Chon loai giao dich can tim: ");
    scanf("%d", &loaiTimKiem);
    xoaBoNhoDem();

    if (loaiTimKiem == 1)
    {
        printf("\nDANH MUC THU NHAP\n");
        printf(" 1. Luong              3. Kinh doanh\n");
        printf(" 2. Thuong             4. Khac (Tu nhap)\n");
        printf("Chon danh muc can tim: ");
        scanf("%d", &chonMuc);
        xoaBoNhoDem();
        switch (chonMuc)
        {
        case 1:
            strcpy(tuKhoa, "Luong");
            break;
        case 2:
            strcpy(tuKhoa, "Thuong");
            break;
        case 3:
            strcpy(tuKhoa, "Kinh doanh");
            break;
        case 4:
            printf("Nhap ten danh muc khac can tim: ");
            fgets(tuKhoa, sizeof(tuKhoa), stdin);
            xoaXuongDong(tuKhoa);
            break;
        default:
            printf(">> Lua chon khong hop le\n");
            return;
        }
    }
    else if (loaiTimKiem == 2)
    {
        printf("\nDANH MUC CHI TIEU\n");
        printf(" 1. An uong             7. Giao duc\n");
        printf(" 2. Chi tieu hang ngay  8. Tien dien\n");
        printf(" 3. Quan ao             9. Di lai\n");
        printf(" 4. My pham            10. Tien nha\n");
        printf(" 5. Phi giao luu       11. Di choi\n");
        printf(" 6. Y te               12. Shopee\n");
        printf(" 13. Muc khac (Tu nhap tu ban phim)\n");
        printf("Chon danh muc can tim (1-13): ");
        scanf("%d", &chonMuc);
        xoaBoNhoDem();
        switch (chonMuc)
        {
        case 1:
            strcpy(tuKhoa, "An uong");
            break;
        case 2:
            strcpy(tuKhoa, "Chi tieu hang ngay");
            break;
        case 3:
            strcpy(tuKhoa, "Quan ao");
            break;
        case 4:
            strcpy(tuKhoa, "My pham");
            break;
        case 5:
            strcpy(tuKhoa, "Phi giao luu");
            break;
        case 6:
            strcpy(tuKhoa, "Y te");
            break;
        case 7:
            strcpy(tuKhoa, "Giao duc");
            break;
        case 8:
            strcpy(tuKhoa, "Tien dien");
            break;
        case 9:
            strcpy(tuKhoa, "Di lai");
            break;
        case 10:
            strcpy(tuKhoa, "Tien nha");
            break;
        case 11:
            strcpy(tuKhoa, "Di choi");
            break;
        case 12:
            strcpy(tuKhoa, "Shopee");
            break;
        case 13:
            printf("Nhap ten danh muc khac can tim: ");
            fgets(tuKhoa, sizeof(tuKhoa), stdin);
            xoaXuongDong(tuKhoa);
            break;
        default:
            printf("Lua chon khong hop le\n");
            return;
        }
    }
    else
    {
        printf("Lua chon khong hop le\n");
        return;
    }

    printf("\nKET QUA TIM KIEM CHO '%s'\n", tuKhoa);
    printf("%-5s %-10s %-15s %-20s %-15s %-20s\n",
           "ID", "Loai", "So Tien", "Danh Muc", "Ngay", "Ghi Chu");

    int timThay = 0;
    for (int i = 0; i < listGD.size; i++)
    {
        if (listGD.data[i].loai == loaiTimKiem && strstr(listGD.data[i].danhMuc, tuKhoa) != NULL)
        {
            char loaiStr[10];
            strcpy(loaiStr, (listGD.data[i].loai == 1) ? "Thu" : "Chi");
            printf("%-5d %-10s %-15.2f %-20s %-15s %-20s\n",
                   listGD.data[i].id, loaiStr, listGD.data[i].soTien, listGD.data[i].danhMuc,
                   listGD.data[i].ngay, listGD.data[i].ghiChu);
            timThay = 1;
        }
    }

    if (!timThay)
    {
        printf("Khong tim thay giao dich nao thuoc danh muc: %s\n", tuKhoa);
    }
}

void xoaGiaoDich(void)
{
    if (listGD.size == 0)
    {
        printf("Danh sach hien tai dang trong\n");
        return;
    }

    int idXoa;
    printf("\nNhap ID giao dich can xoa: ");
    scanf("%d", &idXoa);
    xoaBoNhoDem();

    int indexXoa = -1;
    // Tìm vị trí của phần tử cần xóa
    for (int i = 0; i < listGD.size; i++)
    {
        if (listGD.data[i].id == idXoa)
        {
            indexXoa = i;
            break;
        }
    }

    if (indexXoa == -1)
    {
        printf("Khong tim thay giao dich co ID %d.\n", idXoa);
        return;
    }

    for (int i = indexXoa; i < listGD.size - 1; i++)
    {
        listGD.data[i] = listGD.data[i + 1];
    }
    listGD.size--;

    tinhSoDu();
    luuFile();
    printf("Da xoa giao dich va cap nhat file\n");
}

void giaiPhongGiaoDich(void) {
    free(listGD.data);
    listGD.data = NULL;
    listGD.size = 0;
    listGD.capacity = 0;
}

void quanLyGiaoDich(void) {
    int luaChon;

    do {
        printf("\nQUAN LY GIAO DICH\n");
        printf("1. Them giao dich moi\n");
        printf("2. Xem danh sach giao dich\n");
        printf("3. Sua giao dich\n");
        printf("4. Xoa giao dich\n");
        printf("5. Tim kiem theo danh muc\n");
        printf("0. Quay lai\n");
        printf("Nhap lua chon: ");
        scanf("%d", &luaChon);
        xoaBoNhoDem();

        switch (luaChon) {
            case 1:
                themGiaoDich();
                break;
            case 2:
                xemDanhSach();
                break;
            case 3:
                suaGiaoDich();
                break;
            case 4:
                xoaGiaoDich();
                break;
            case 5:
                timKiem();
                break;
            case 0:
                break;
            default:
                printf("Lua chon khong hop le. Vui long thu lai\n");
        }
    } while (luaChon != 0);
}
