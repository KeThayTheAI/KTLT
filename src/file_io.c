#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "models.h"
#include "utils.h"
#include "transaction.h"
#include "budget.h"
#include "file_io.h"

void docFile(void)
{
    FILE *file = fopen(FILE_NAME, "r");
    if (!file)
    {
        printf("Chua co file du lieu. Se tao file moi khi luu.\n");
        return;
    }

    char line[256];
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file))
    {
        GiaoDich gd;
        char *token = strtok(line, ",");
        if (token == NULL)
            continue;
        gd.id = atoi(token);

        token = strtok(NULL, ",");
        if (token)
            gd.loai = atoi(token);
        else
            continue;

        token = strtok(NULL, ",");
        if (token)
            gd.soTien = atof(token);
        else
            continue;

        token = strtok(NULL, ",");
        if (token)
        {
            strncpy(gd.danhMuc, token, sizeof(gd.danhMuc) - 1);
            gd.danhMuc[sizeof(gd.danhMuc) - 1] = '\0';
        }
        else
            continue;

        token = strtok(NULL, ",");
        if (token)
        {
            strncpy(gd.ngay, token, sizeof(gd.ngay) - 1);
            gd.ngay[sizeof(gd.ngay) - 1] = '\0';
        }
        else
            continue;

        token = strtok(NULL, "\n");
        if (token)
        {
            strncpy(gd.ghiChu, token, sizeof(gd.ghiChu) - 1);
            gd.ghiChu[sizeof(gd.ghiChu) - 1] = '\0';
        }
        else
            strcpy(gd.ghiChu, "");

        if (kiemTraNgayHopLe(gd.ngay) && (gd.loai == 1 || gd.loai == 2) && gd.soTien >= 0)
        {
            themVaoCuoiDanhSach(gd);
        }
    }
    fclose(file);
    sapXepTheoNgay();
    tinhSoDu();
}

void luuFile(void)
{
    FILE *file = fopen(FILE_NAME, "w");
    if (!file)
    {
        printf("Loi: Khong the mo file de ghi!\n");
        return;
    }

    sapXepTheoNgay();
    fprintf(file, "ID,Loai(1:Thu/2:Chi),SoTien,DanhMuc,Ngay,GhiChu\n");
    for (int i = 0; i < listGD.size; i++)
    {
        char danhMuc[50];
        char ghiChu[100];
        strncpy(danhMuc, listGD.data[i].danhMuc, sizeof(danhMuc) - 1);
        danhMuc[sizeof(danhMuc) - 1] = '\0';
        strncpy(ghiChu, listGD.data[i].ghiChu, sizeof(ghiChu) - 1);
        ghiChu[sizeof(ghiChu) - 1] = '\0';
        chuanHoaChuoiFile(danhMuc);
        chuanHoaChuoiFile(ghiChu);
        fprintf(file, "%d,%d,%.2f,%s,%s,%s\n",
                listGD.data[i].id, listGD.data[i].loai, listGD.data[i].soTien,
                danhMuc, listGD.data[i].ngay, ghiChu);
    }
    fclose(file);
}

void docFileNganSach(void)
{
    FILE *file = fopen(FILE_NGANSACH, "r");
    if (!file)
        return;

    char line[256];
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file))
    {
        NganSach ns;
        char *token = strtok(line, ",");
        if (token == NULL)
            continue;
        strncpy(ns.danhMuc, token, sizeof(ns.danhMuc) - 1);
        ns.danhMuc[sizeof(ns.danhMuc) - 1] = '\0';

        token = strtok(NULL, ",");
        if (token)
            ns.thang = atoi(token);
        else
            continue;

        token = strtok(NULL, ",");
        if (token)
            ns.nam = atoi(token);
        else
            continue;

        token = strtok(NULL, "\n");
        if (token)
            ns.hanMuc = atof(token);
        else
            continue;

        if (ns.thang >= 1 && ns.thang <= 12 && ns.nam >= 1900 && ns.nam <= 2100 && ns.hanMuc >= 0)
        {
            themNganSachVaoList(ns);
        }
    }
    fclose(file);
}

void luuFileNganSach(void)
{
    FILE *file = fopen(FILE_NGANSACH, "w");
    if (!file)
        return;

    fprintf(file, "DanhMuc,Thang,Nam,HanMuc\n");
    for (int i = 0; i < listNS.size; i++)
    {
        char danhMuc[50];
        strncpy(danhMuc, listNS.data[i].danhMuc, sizeof(danhMuc) - 1);
        danhMuc[sizeof(danhMuc) - 1] = '\0';
        chuanHoaChuoiFile(danhMuc);
        fprintf(file, "%s,%d,%d,%.2f\n",
                danhMuc, listNS.data[i].thang,
                listNS.data[i].nam, listNS.data[i].hanMuc);
    }
    fclose(file);
}
