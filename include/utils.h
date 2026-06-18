#ifndef UTILS_H
#define UTILS_H

void xoaBoNhoDem(void);
void xoaXuongDong(char* str);
void chuanHoaChuoiFile(char* str);
int laNamNhuan(int year);
int kiemTraNgayHopLe(char* ngayStr);
int tachNgay(char* ngayStr, int* ngay, int* thang, int* nam);
int soSanhNgay(char* ngay1, char* ngay2);

#endif
