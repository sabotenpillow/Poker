//====================================================================
//  工学部「情報環境実験２」(富永)  C言語プログラミング  例題
//  ポーカーゲームの戦略
//--------------------------------------------------------------------
//  Poker  usr/s13t200_03/  PokerOpe.c
//  Linux CentOS 6.7  GCC 4.4.7
//--------------------------------------------------------------------
//  富永研究室  tominaga 富永浩之
//  2015.11.17
//====================================================================


//====================================================================
//  仕様
//====================================================================

/*--------------------------------------------------------------------

手札、場札、チェンジ数、テイク数、捨札を引数とし、捨札を決める。
返却値は、捨札の位置である。-1のときは、交換しないで、手札を確定させる。
関数 strategy() は、戦略のインタフェースであり、この関数内で、
実際の戦略となる関数を呼び出す。手札と捨札は、不正防止のため、
変更不可なので、局所配列にコピーして、整列などの処理を行う。
複数の戦略を比較したり、パラメタを変化させて、より強い戦略を目指す。

---------------------------------------------------------------------*/


//====================================================================
//  前処理
//====================================================================

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Poker.h"

//--------------------------------------------------------------------
//  関数宣言
//--------------------------------------------------------------------



//====================================================================
//  戦略
//====================================================================

/*--------------------------------------------------------------------
//  ユーザ指定
//--------------------------------------------------------------------

最初の手札のまま交換しない。

hd : 手札配列
fd : 場札配列(テイク内の捨札)
cg : チェンジ数
tk : テイク数
ud : 捨札配列(過去のテイクも含めた全ての捨札)
us : 捨札数

--------------------------------------------------------------------*/

int strategy(const int hd[], const int fd[], int cg, int tk, const int ud[], int us)
{
  int point = poker_point(hd);
  int val[5] = {0};
  int kindVal = 3;
  int numVal = 4;
  int seqVal = 6;
  int ret_card;
  int i, j;

  if ( point > P3 ) { return -1; }
  // same kind pair
  for ( i = 0; i < HNUM; i++ ) {
    for ( j = i+1; j < HNUM; j++ ) {
      if ( hd[i] % 4 == hd[j] % 4 ) { val[i]++; val[j]++; }
    }
  }

  // same number pair
  for ( i = 0; i < HNUM; i++ ) {
    for ( j = i+1; j < HNUM; j++ ) {
      if ( hd[i] % 13 == hd[j] % 13 ) { val[i]+=numVal; val[j]+=numVal; }
    }
  }

  // sequential number

  // return minimum value card
  ret_card = 0;
  for ( i = 1; i < HNUM; i++ ) {
    if ( val[ret_card] > val[i] ) { ret_card = i; }
  }
  // return ( ret_card < 5 ) ? ret_card : -1;
  return ret_card;
}


//====================================================================
//  補助関数
//====================================================================
