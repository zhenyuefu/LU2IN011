
#include "stdio.h"
#include <string.h>

// 把浮点数的整数部分转换为二进制的字符串。
// dec：待转换的浮点数的整数部分。
// pbin：用于存放转换后的字符串的地址。
void dectobin(const long dec, char *pbin) {
  long ys = 0; // 余数。
  int s = dec; // 商。
  int ii = 0;  // 位数的计数器。
  char result[65]; // 转换成二进制后，保存在result中，再反过来存放到pbin中。

  memset(result, 0, sizeof(result));

  // 把浮点数的整数部分转换为二进制，存放在result中。
  while (s > 0) {
    ys = s % 2;
    s = s / 2;
    result[ii] = ys + '0';
    ii++;
  }

  // 再把result字符串反过来，存放在pbin中。
  int jj = 0;
  for (; ii > 0; ii--) {
    pbin[jj] = result[ii - 1];
    jj++;
  }

  pbin[jj] = 0; // 出于安全的考虑，加上0表示字符串结束。
}

// 把浮点数小数部分转换为二进制的字符串。
// decp：待转换的浮点数的小数部分。
// pbin：用于存放转换后的字符串的地址。
// maxp：指定pbin字符串保留的长度。
void decptobin(const double decp, char *pbin, const int maxp) {
  double xs = decp; // 小数部分。
  int qz = 0;       // 取整的结果。
  int ii = 0;       // 位数的计数器。

  while (xs > 0) {
    qz = (int)(xs * 2);    // 小数部分乘2取整。
    pbin[ii++] = qz + '0'; // 0+'0'='0'，1+'0'='1'。
    xs = xs * 2;           // 小数部分乘2。
    if (xs >= 1)
      xs = xs - 1; // 如果>=1，取整。

    if (ii == maxp)
      break;
  }

  pbin[ii] = 0; // 出于安全的考虑，加上0表示字符串结束。
}

int main() {
  double ff = 0;
  printf("请输入一个浮点数：");
  scanf("%lf", &ff);

  char str1[101], str2[101];
  memset(str1, 0, sizeof(str1));

  dectobin((long)ff, str1); // 把整数部分转换为二进制，保存在str1中。
  decptobin(ff - (long)ff, str2, 24); // 把小数部分转换为二进制，保存在str2中。

  printf("%f的二进制输出是：%s.%s\n", ff, str1, str2);
}