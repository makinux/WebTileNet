
#include <stdlib.h>
#include <math.h>

float static_buffer[253010819];
float* dynamic_buffer = nullptr;

int meta_buf_0[] = {251540355,251147139,65536,3,3,65536};
int meta_buf_1[] = {251147139,238957443,1,3,256,256,256,256,3,3,1,1,1,1,1,1};
int meta_buf_2[] = {238957443,0,192820099,65536,64,27};
int meta_buf_3[] = {1728,192820099,217985923,64,65536,64,65536,1045220557};
int meta_buf_4[] = {217985923,213791619,65536,64,64,65536};
int meta_buf_5[] = {213791619,129905539,1,64,256,256,128,128,4,4,1,1,2,2,1,1};
int meta_buf_6[] = {129905539,1792,232665987,16384,128,1024};
int meta_buf_7[] = {132864,232665987,236860291,128,16384,128,16384,1045220557};
int meta_buf_8[] = {236860291,234763139,16384,128,128,16384};
int meta_buf_9[] = {234763139,180237187,1,128,128,128,64,64,4,4,1,1,2,2,1,1};
int meta_buf_10[] = {180237187,132992,245969795,4096,256,2048};
int meta_buf_11[] = {657280,245969795,244921219,256,4096,256,4096,1045220557};
int meta_buf_12[] = {244921219,243872643,4096,256,256,4096};
int meta_buf_13[] = {243872643,197014403,1,256,64,64,32,32,4,4,1,1,2,2,1,1};
int meta_buf_14[] = {197014403,657536,250164099,1024,512,4096};
int meta_buf_15[] = {2754688,250164099,247542659,512,1024,512,1024,1045220557};
int meta_buf_16[] = {247542659,247018371,1024,512,512,1024};
int meta_buf_17[] = {247018371,226374531,1,512,32,32,16,16,4,4,1,1,2,2,1,1};
int meta_buf_18[] = {226374531,2755200,252523395,256,512,8192};
int meta_buf_19[] = {6949504,252523395,252392323,512,256,512,256,1045220557};
int meta_buf_20[] = {252392323,251999107,256,512,512,256};
int meta_buf_21[] = {251999107,248066947,1,512,16,16,8,8,4,4,1,1,2,2,1,1};
int meta_buf_22[] = {248066947,6950016,252752771,64,512,8192};
int meta_buf_23[] = {11144320,252752771,252720003,512,64,512,64,1045220557};
int meta_buf_24[] = {252720003,252851075,64,512,512,64};
int meta_buf_25[] = {252851075,252261251,1,512,8,8,4,4,4,4,1,1,2,2,1,1};
int meta_buf_26[] = {252261251,11144832,252998531,16,512,8192};
int meta_buf_27[] = {15339136,252998531,252965763,512,16,512,16,1045220557};
int meta_buf_28[] = {252965763,252973955,16,512,512,16};
int meta_buf_29[] = {252973955,252785539,1,512,4,4,2,2,4,4,1,1,2,2,1,1};
int meta_buf_30[] = {252785539,15339648,253006723,4,512,8192};
int meta_buf_31[] = {19533952,253006723,253008771,512,512,512,4,1045220557};
int meta_buf_32[] = {253008771,19534464,252883843,4,8192,512};
int meta_buf_33[] = {252982147,252883843,1,2,2,512,4,4,4,4,2,2,1,1};
int meta_buf_34[] = {23728768,23729280,252982147,252990339,512,16,512,16};
int meta_buf_35[] = {252949379,4,2,252990339,252965763,1,1,16384,1,4096,1024,16384,1,4096,1024,1,512,4,4,1,512,4,4,0,512};
int meta_buf_36[] = {252949379,23729792,251736963,16,8192,1024};
int meta_buf_37[] = {252818307,251736963,1,4,4,512,8,8,4,4,2,2,1,1};
int meta_buf_38[] = {32118912,32118400,252818307,252916611,512,64,512,64};
int meta_buf_39[] = {252654467,4,2,252916611,252720003,1,1,65536,1,8192,1024,65536,1,8192,1024,1,512,8,8,1,512,8,8,0,512};
int meta_buf_40[] = {252654467,32119424,248591235,64,8192,1024};
int meta_buf_41[] = {252130179,248591235,1,8,8,512,16,16,4,4,2,2,1,1};
int meta_buf_42[] = {40508544,40508032,252130179,251868035,512,256,512,256};
int meta_buf_43[] = {250688387,4,2,251868035,252392323,1,1,262144,1,16384,1024,262144,1,16384,1024,1,512,16,16,1,512,16,16,0,512};
int meta_buf_44[] = {250688387,40509056,230568835,256,8192,1024};
int meta_buf_45[] = {249115523,230568835,1,16,16,512,32,32,4,4,2,2,1,1};
int meta_buf_46[] = {48897664,48898176,249115523,249639811,512,1024,512,1024};
int meta_buf_47[] = {242824067,4,2,249639811,247542659,1,1,1048576,1,32768,1024,1048576,1,32768,1024,1,512,32,32,1,512,32,32,0,512};
int meta_buf_48[] = {242824067,48898688,201208707,1024,4096,1024};
int meta_buf_49[] = {240726915,201208707,1,32,32,256,64,64,4,4,2,2,1,1};
int meta_buf_50[] = {53092992,53093248,240726915,241775491,256,4096,256,4096};
int meta_buf_51[] = {228471683,4,2,241775491,244921219,1,1,2097152,1,32768,512,2097152,1,32768,512,1,256,64,64,1,256,64,64,0,256};
int meta_buf_52[] = {228471683,53093504,163459971,4096,2048,512};
int meta_buf_53[] = {222180227,163459971,1,64,64,128,128,128,4,4,2,2,1,1};
int meta_buf_54[] = {54142080,54142208,222180227,224277379,128,16384,128,16384};
int meta_buf_55[] = {188625795,4,2,224277379,236860291,1,1,4194304,1,32768,256,4194304,1,32768,256,1,128,128,128,1,128,128,128,0,128};
int meta_buf_56[] = {188625795,54142336,146682755,16384,1024,256};
int meta_buf_57[] = {209597315,146682755,1,128,128,64,256,256,4,4,2,2,1,1};
int meta_buf_58[] = {54404480,54404544,209597315,205403011,64,65536,64,65536};
int meta_buf_59[] = {171848579,4,2,205403011,217985923,1,1,8388608,1,32768,128,8388608,1,32768,128,1,64,256,256,1,64,256,256,0,64};
int meta_buf_60[] = {171848579,54408067,1,128,256,256,256,256,3,3,1,1,1,1,1,1};
int meta_buf_61[] = {54408067,54404608,250950531,65536,3,1152};
int meta_buf_62[] = {54408064,250950531,251343747,3,65536,3,65536};
int* meta_buffers[] = {meta_buf_0,meta_buf_1,meta_buf_2,meta_buf_3,meta_buf_4,meta_buf_5,meta_buf_6,meta_buf_7,meta_buf_8,meta_buf_9,meta_buf_10,meta_buf_11,meta_buf_12,meta_buf_13,meta_buf_14,meta_buf_15,meta_buf_16,meta_buf_17,meta_buf_18,meta_buf_19,meta_buf_20,meta_buf_21,meta_buf_22,meta_buf_23,meta_buf_24,meta_buf_25,meta_buf_26,meta_buf_27,meta_buf_28,meta_buf_29,meta_buf_30,meta_buf_31,meta_buf_32,meta_buf_33,meta_buf_34,meta_buf_35,meta_buf_36,meta_buf_37,meta_buf_38,meta_buf_39,meta_buf_40,meta_buf_41,meta_buf_42,meta_buf_43,meta_buf_44,meta_buf_45,meta_buf_46,meta_buf_47,meta_buf_48,meta_buf_49,meta_buf_50,meta_buf_51,meta_buf_52,meta_buf_53,meta_buf_54,meta_buf_55,meta_buf_56,meta_buf_57,meta_buf_58,meta_buf_59,meta_buf_60,meta_buf_61,meta_buf_62};

extern "C" void init() {
    //static_buffer = (float*)malloc(253010819 * sizeof(float));
}

extern "C" float* get_static_buffer(void) {
    return static_buffer;
}

extern "C" float* allocate_dynamic_buffer(int count) {
    if (dynamic_buffer) {
        free(dynamic_buffer);
        dynamic_buffer = nullptr;
    }
    dynamic_buffer = (float*)malloc(count * sizeof(float));
    return dynamic_buffer;
}

extern "C" float* get_dynamic_buffer(void) {
    return dynamic_buffer;
}
extern "C" void set_placeholder_value(int kernel_order, int offset, int value) {
    meta_buffers[kernel_order][offset] = value;
}

void transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    float * v2 = (static_buffer + meta_buffer[1]);
    const int v3 = meta_buffer[2];
    const int v4 = meta_buffer[3];
    const int D0 = meta_buffer[4];
    const int D1 = meta_buffer[5];
    int d0;
    for (d0 = ((1 > 8) ? (0 % (1 / 8)) : 0); d0 < D0; d0 += ((1 > 8) ? (1 / 8) : 1)) {
        int d1;
        for (d1 = ((1 > 8) ? (0 / (1 / 8)) : 0); d1 < D1; d1 += ((1 > 8) ? 8 : 1)) {
            const float v5 = v1[d0*v3 + d1];
            float v6;
            {
                v6 = v5;
            }
            v2[d0 + d1*v4] = v6;
        }
    }
}


void im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(const int * meta_buffer)
{
    const float *im = (static_buffer + meta_buffer[0]);
    float *col = (static_buffer + meta_buffer[1]);

    const int N = meta_buffer[2];
    const int C1 = meta_buffer[3];
    const int H1 = meta_buffer[4];
    const int W1 = meta_buffer[5];
    const int H2 = meta_buffer[6];
    const int W2 = meta_buffer[7];
    const int KH = meta_buffer[8];
    const int KW = meta_buffer[9];
    const int DH = meta_buffer[10];
    const int DW = meta_buffer[11];
    const int SH = meta_buffer[12];
    const int SW = meta_buffer[13];
    const int PH = meta_buffer[14];
    const int PW = meta_buffer[15];

    for (int gid = 0; gid < N*H2*W2*KH*KW*C1; gid += 1) {
        const int c1 = gid % C1;
        const int kw = gid / C1 % KW;
        const int kh = gid / C1 / KW % KH;
        const int w2 = gid / C1 / KW / KH % W2;
        const int h2 = gid / C1 / KW / KH / W2 % H2;
        const int  n = gid / C1 / KW / KH / W2 / H2;

        const int h1 = h2 * SH - PH + kh * DH;
        const int w1 = w2 * SW - PW + kw * DW;

        col[gid] = (h1 < 0 || h1 >= H1 || w1 < 0 || w1 >= W1) ? 0 : im[((n*H1+h1)*W1+w1)*C1+c1];
    }
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(const int * meta_buffer)
{
    float *A = (static_buffer + meta_buffer[0]);
    float *B = (static_buffer + meta_buffer[1]);
    float *C = (static_buffer + meta_buffer[2]);

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, meta_buffer[3], meta_buffer[5]);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor> > b_mat(B, meta_buffer[5], meta_buffer[4]);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, meta_buffer[3], meta_buffer[4]);

    c_mat.noalias() = a_mat * b_mat;
}


void fusedelementwise_fe195dcdb65acbdea4fbe0996136d0fb4b8c878447bfb579150afca2(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    const float * v2 = (static_buffer + meta_buffer[1]);
    float * v3 = (static_buffer + meta_buffer[2]);
    const int v4 = meta_buffer[3];
    const int v5 = meta_buffer[4];
    const int D0 = meta_buffer[5];
    const int D1 = meta_buffer[6];
    int d0;
    for (d0 = ((1 > 8) ? (0 % (1 / 8)) : 0); d0 < D0; d0 += ((1 > 8) ? (1 / 8) : 1)) {
        const float v6 = v1[d0];
        int d1;
        for (d1 = ((1 > 8) ? (0 / (1 / 8)) : 0); d1 < D1; d1 += ((1 > 8) ? 8 : 1)) {
            const float v7 = v2[d0 + d1*v4];
            float v8;
            {
                v8 = v7 + v6;
            }
            float v9;
            {
                float slope = *((float *)(&meta_buffer[7]));
                v9 = v8 > 0 ? v8 : (v8 * slope);
            }
            v3[d0*v5 + d1] = v9;
        }
    }
}


void fusedelementwise_7aa3bcd3f1d748cc563d29aadee56048375fb307106692ef072185ef(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    const float * v2 = (static_buffer + meta_buffer[1]);
    float * v3 = (static_buffer + meta_buffer[2]);
    const int v4 = meta_buffer[3];
    const int v5 = meta_buffer[4];
    const int D0 = meta_buffer[5];
    const int D1 = meta_buffer[6];
    int d0;
    for (d0 = ((1 > 8) ? (0 % (1 / 8)) : 0); d0 < D0; d0 += ((1 > 8) ? (1 / 8) : 1)) {
        const float v6 = v1[d0];
        int d1;
        for (d1 = ((1 > 8) ? (0 / (1 / 8)) : 0); d1 < D1; d1 += ((1 > 8) ? 8 : 1)) {
            const float v7 = v2[d0 + d1*v4];
            float v8;
            {
                v8 = v7 + v6;
            }
            float v9;
            {
                float slope = *((float *)(&meta_buffer[7]));
                v9 = v8 > 0 ? v8 : (v8 * slope);
            }
            v3[d0 + d1*v5] = v9;
        }
    }
}


void col2im_73909fb9a6e4f41fa36d633023909781659562b6438922487c8f9efc(const int * meta_buffer)
{
    const float *col = (static_buffer + meta_buffer[1]);
    float *im = (static_buffer + meta_buffer[0]);

    const int N = meta_buffer[2];
    const int C1 = meta_buffer[5];
    const int H1 = meta_buffer[6];
    const int W1 = meta_buffer[7];
    const int H2 = meta_buffer[3];
    const int W2 = meta_buffer[4];
    const int KH = meta_buffer[8];
    const int KW = meta_buffer[9];
    const int SH = meta_buffer[10];
    const int SW = meta_buffer[11];
    const int PH = meta_buffer[12];
    const int PW = meta_buffer[13];

    for (int gid = 0; gid < N*H1*W1*C1; gid += 1) {
        const int c1 = gid % C1;
        const int w1 = gid / C1 % W1;
        const int h1 = gid / C1 / W1 % H1;
        const int n = gid / C1 / W1 / H1;

        float sum = 0;
        for (int kh = 0; kh < KH; kh++) {
            const int h2 = (h1 + PH - kh) / SH;
            if ((h1 + PH - kh) % SH != 0 || h2 < 0 || h2 >= H2) continue;

            for (int kw = 0; kw < KW; kw++) {
                const int w2 = (w1 + PW - kw) / SW;
                if ((w1 + PW - kw) % SW != 0 || w2 < 0 || w2 >= W2) continue;

                sum += col[((((n * H2 + h2) * W2 + w2) * KH + kh) * KW + kw) * C1 + c1];
            }
        }

        im[gid] = sum;
    }
}


void fusedelementwise_255ff7fbed9884857926a1ee4f6c1d09102d9b8c9ba80e3138f3e59b(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    const float * v2 = (static_buffer + meta_buffer[1]);
    const float * v3 = (static_buffer + meta_buffer[2]);
    float * v4 = (static_buffer + meta_buffer[3]);
    const int v5 = meta_buffer[4];
    const int v6 = meta_buffer[5];
    const int D0 = meta_buffer[6];
    const int D1 = meta_buffer[7];
    int d0;
    for (d0 = ((1 > 8) ? (0 % (1 / 8)) : 0); d0 < D0; d0 += ((1 > 8) ? (1 / 8) : 1)) {
        const float v7 = v1[d0];
        const float v8 = v2[d0];
        int d1;
        for (d1 = ((1 > 8) ? (0 / (1 / 8)) : 0); d1 < D1; d1 += ((1 > 8) ? 8 : 1)) {
            const float v9 = v3[d0 + d1*v5];
            float v10;
            {
                v10 = v9 * v8;
            }
            float v11;
            {
                v11 = v10 + v7;
            }
            float v12;
            {
                v12 = v11 > 0 ? v11 : 0;
            }
            v4[d0*v6 + d1] = v12;
        }
    }
}


void concat_de57edf7b15e96b288eb0fab9c3b5ec2a2f6df54ec623ea33d5a4d30(const int * meta_buffer)
{
    float *y = (static_buffer + meta_buffer[0]);
    const int N = meta_buffer[2];
    const int D = meta_buffer[1];
    const int *y_offsets = (&(meta_buffer[23]));
    const int *x_shapes = (&(meta_buffer[15]));
    const int *x_strides_in_y = (&(meta_buffer[7]));

    int x_index = 0;

    for (int n = 0; n < N; n++) {
        const float *x = (meta_buffer[3+2+ (n)] ? static_buffer : dynamic_buffer) + meta_buffer[3 + (n)];
        const int y_offset = y_offsets[n];
        const int *x_shape = x_shapes + n * D;
        const int *x_stride_in_y = x_strides_in_y + n * D;

        int x_size = 1;
        for (int d = 0; d < D; d++) {
            x_size *= x_shape[d];
        }

        while (x_index < x_size) {
            int y_index = y_offset;
            int s = x_index;
            for (int d = D-1; d >= 0; d--) {
                y_index += x_stride_in_y[d] * (s % x_shape[d]);
                s /= x_shape[d];
            }

            y[y_index] = x[x_index];

            x_index++;
        }

        x_index -= x_size;
    }
}


void fusedelementwise_a5cca09bfe3ba8cbbe45eea2f9e9c56212d6eb8290c280e6b12f2c21(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    const float * v2 = (static_buffer + meta_buffer[1]);
    const float * v3 = (static_buffer + meta_buffer[2]);
    float * v4 = (static_buffer + meta_buffer[3]);
    const int v5 = meta_buffer[4];
    const int v6 = meta_buffer[5];
    const int D0 = meta_buffer[6];
    const int D1 = meta_buffer[7];
    int d0;
    for (d0 = ((1 > 8) ? (0 % (1 / 8)) : 0); d0 < D0; d0 += ((1 > 8) ? (1 / 8) : 1)) {
        const float v7 = v1[d0];
        const float v8 = v2[d0];
        int d1;
        for (d1 = ((1 > 8) ? (0 / (1 / 8)) : 0); d1 < D1; d1 += ((1 > 8) ? 8 : 1)) {
            const float v9 = v3[d0 + d1*v5];
            float v10;
            {
                v10 = v9 * v7;
            }
            float v11;
            {
                v11 = v10 + v8;
            }
            float v12;
            {
                v12 = v11 > 0 ? v11 : 0;
            }
            v4[d0*v6 + d1] = v12;
        }
    }
}


void fusedelementwise_755f36aa803133808d65cebb4bdca9f54486df34e0eb6728cb7bd3d5(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    const float * v2 = (static_buffer + meta_buffer[1]);
    float * v3 = (static_buffer + meta_buffer[2]);
    const int v4 = meta_buffer[3];
    const int v5 = meta_buffer[4];
    const int D0 = meta_buffer[5];
    const int D1 = meta_buffer[6];
    int d0;
    for (d0 = ((1 > 8) ? (0 % (1 / 8)) : 0); d0 < D0; d0 += ((1 > 8) ? (1 / 8) : 1)) {
        const float v6 = v1[d0];
        int d1;
        for (d1 = ((1 > 8) ? (0 / (1 / 8)) : 0); d1 < D1; d1 += ((1 > 8) ? 8 : 1)) {
            const float v7 = v2[d0 + d1*v4];
            float v8;
            {
                v8 = v7 + v6;
            }
            float v9;
            {
                v9 = tanh(v8);
            }
            v3[d0*v5 + d1] = v9;
        }
    }
}

extern "C" void run() {
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_0);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_1);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_2);
fusedelementwise_fe195dcdb65acbdea4fbe0996136d0fb4b8c878447bfb579150afca2(meta_buf_3);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_4);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_5);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_6);
fusedelementwise_fe195dcdb65acbdea4fbe0996136d0fb4b8c878447bfb579150afca2(meta_buf_7);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_8);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_9);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_10);
fusedelementwise_fe195dcdb65acbdea4fbe0996136d0fb4b8c878447bfb579150afca2(meta_buf_11);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_12);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_13);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_14);
fusedelementwise_fe195dcdb65acbdea4fbe0996136d0fb4b8c878447bfb579150afca2(meta_buf_15);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_16);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_17);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_18);
fusedelementwise_fe195dcdb65acbdea4fbe0996136d0fb4b8c878447bfb579150afca2(meta_buf_19);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_20);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_21);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_22);
fusedelementwise_fe195dcdb65acbdea4fbe0996136d0fb4b8c878447bfb579150afca2(meta_buf_23);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_24);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_25);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_26);
fusedelementwise_fe195dcdb65acbdea4fbe0996136d0fb4b8c878447bfb579150afca2(meta_buf_27);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_28);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_29);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_30);
fusedelementwise_7aa3bcd3f1d748cc563d29aadee56048375fb307106692ef072185ef(meta_buf_31);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_32);
col2im_73909fb9a6e4f41fa36d633023909781659562b6438922487c8f9efc(meta_buf_33);
fusedelementwise_255ff7fbed9884857926a1ee4f6c1d09102d9b8c9ba80e3138f3e59b(meta_buf_34);
concat_de57edf7b15e96b288eb0fab9c3b5ec2a2f6df54ec623ea33d5a4d30(meta_buf_35);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_36);
col2im_73909fb9a6e4f41fa36d633023909781659562b6438922487c8f9efc(meta_buf_37);
fusedelementwise_a5cca09bfe3ba8cbbe45eea2f9e9c56212d6eb8290c280e6b12f2c21(meta_buf_38);
concat_de57edf7b15e96b288eb0fab9c3b5ec2a2f6df54ec623ea33d5a4d30(meta_buf_39);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_40);
col2im_73909fb9a6e4f41fa36d633023909781659562b6438922487c8f9efc(meta_buf_41);
fusedelementwise_a5cca09bfe3ba8cbbe45eea2f9e9c56212d6eb8290c280e6b12f2c21(meta_buf_42);
concat_de57edf7b15e96b288eb0fab9c3b5ec2a2f6df54ec623ea33d5a4d30(meta_buf_43);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_44);
col2im_73909fb9a6e4f41fa36d633023909781659562b6438922487c8f9efc(meta_buf_45);
fusedelementwise_255ff7fbed9884857926a1ee4f6c1d09102d9b8c9ba80e3138f3e59b(meta_buf_46);
concat_de57edf7b15e96b288eb0fab9c3b5ec2a2f6df54ec623ea33d5a4d30(meta_buf_47);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_48);
col2im_73909fb9a6e4f41fa36d633023909781659562b6438922487c8f9efc(meta_buf_49);
fusedelementwise_255ff7fbed9884857926a1ee4f6c1d09102d9b8c9ba80e3138f3e59b(meta_buf_50);
concat_de57edf7b15e96b288eb0fab9c3b5ec2a2f6df54ec623ea33d5a4d30(meta_buf_51);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_52);
col2im_73909fb9a6e4f41fa36d633023909781659562b6438922487c8f9efc(meta_buf_53);
fusedelementwise_255ff7fbed9884857926a1ee4f6c1d09102d9b8c9ba80e3138f3e59b(meta_buf_54);
concat_de57edf7b15e96b288eb0fab9c3b5ec2a2f6df54ec623ea33d5a4d30(meta_buf_55);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_56);
col2im_73909fb9a6e4f41fa36d633023909781659562b6438922487c8f9efc(meta_buf_57);
fusedelementwise_255ff7fbed9884857926a1ee4f6c1d09102d9b8c9ba80e3138f3e59b(meta_buf_58);
concat_de57edf7b15e96b288eb0fab9c3b5ec2a2f6df54ec623ea33d5a4d30(meta_buf_59);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_60);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_61);
fusedelementwise_755f36aa803133808d65cebb4bdca9f54486df34e0eb6728cb7bd3d5(meta_buf_62);

}

