#ifndef REPORT_H
#define REPORT_H

#include "models.h"

void themThongKeDanhMuc(ListThongKe* tk, char* danhMuc, double soTien);
int giaoDichThuocKyThongKe(GiaoDich gd, int locTheoThang, int thang, int nam);
void inThongKeDanhMuc(char* tieuDe, ListThongKe* tk, double tongTien);
void thongKe(void);

#endif
