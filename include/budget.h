#ifndef BUDGET_H
#define BUDGET_H

#include "models.h"

void themNganSachVaoList(NganSach ns);
int timViTriNganSach(char* danhMuc, int thang, int nam);
double tinhTongChiDanhMucTheoThang(char* danhMuc, int thang, int nam);
void canhBaoVuotNganSach(GiaoDich gd);
void inCanhBaoVuotNganSachTheoKy(int locTheoThang, int thang, int nam);

void thietLapNganSach(void);
void xemNganSach(void);
void suaNganSach(void);
void xoaNganSach(void);
void quanLyNganSach(void);
void giaiPhongNganSach(void);

#endif
