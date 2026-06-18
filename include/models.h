#ifndef MODELS_H
#define MODELS_H

#define FILE_NAME "data.csv"
#define FILE_NGANSACH "ngansach.csv"

#define MAX_CATEGORY 50
#define MAX_DATE 15
#define MAX_NOTE 100

typedef struct
{
    int id;
    int loai; // 1: Thu nhập, 2: Chi tiêu
    double soTien;
    char danhMuc[MAX_CATEGORY];
    char ngay[MAX_DATE];
    char ghiChu[MAX_NOTE];
} GiaoDich;

typedef struct
{
    GiaoDich *data;
    int size;
    int capacity;
} ListGiaoDich;

typedef struct
{
    char danhMuc[MAX_CATEGORY];
    int thang;
    int nam;
    double hanMuc;
} NganSach;

typedef struct
{
    NganSach *data;
    int size;
    int capacity;
} ListNganSach;

typedef struct
{
    char danhMuc[MAX_CATEGORY];
    double tongTien;
} ThongKeDanhMuc;

typedef struct
{
    ThongKeDanhMuc *data;
    int size;
    int capacity;
} ListThongKe;

extern ListGiaoDich listGD;
extern ListNganSach listNS;
extern double soDu;

#endif
