#include <stdio.h>
#include <string.h>
#include "utils.h"

void xoaBoNhoDem(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void xoaXuongDong(char *str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
    }
}

void chuanHoaChuoiFile(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ',' || str[i] == '\n' || str[i] == '\r')
        {
            str[i] = ' ';
        }
    }
}

int laNamNhuan(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int kiemTraNgayHopLe(char *ngayStr)
{
    int d, m, y;
    if (sscanf(ngayStr, "%d/%d/%d", &d, &m, &y) != 3)
        return 0;
    if (y < 1900 || y > 2100 || m < 1 || m > 12 || d < 1)
        return 0;
    int soNgayTrongThang[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (laNamNhuan(y))
        soNgayTrongThang[2] = 29;
    if (d > soNgayTrongThang[m])
        return 0;
    return 1;
}

int tachNgay(char *ngayStr, int *ngay, int *thang, int *nam)
{
    return sscanf(ngayStr, "%d/%d/%d", ngay, thang, nam) == 3;
}

int soSanhNgay(char *ngay1, char *ngay2)
{
    int d1, m1, y1, d2, m2, y2;
    if (!tachNgay(ngay1, &d1, &m1, &y1))
        return 1;
    if (!tachNgay(ngay2, &d2, &m2, &y2))
        return -1;
    if (y1 != y2)
        return y1 - y2;
    if (m1 != m2)
        return m1 - m2;
    if (d1 != d2)
        return d1 - d2;
    return 0;
}
