#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <dos.h>
#include "win32_helper.h"
#include "intro.h"
#include "help.h"

/* ���ᠭ�� ��������� ����ᮢ */
/* � �� ��砫�� ���祭�� */
long money=10000; // ���죨, ��
long gold=0;     // �����, ��
long land=100;   // �����, ��
long zerno=1000;  // ��୮, ⮭�
long krest=100;  // �����ﭥ, ���
long guard=100;  // ���न�, 祫

/* ⥪�饥 ���ﭨ� ����ᮢ */
long cur_money,cur_gold,cur_land,cur_zerno,cur_krest,cur_guard;
long build_xram;   // ����஥�� �ࠬ��
long ochki;        // ���࠭�� ��஢� �窨

/* �।��� 業� */
long pr_gold=1000;   // ��/��
long pr_land=200;    // ��/��
long pr_zerno=10;    // ��/⮭�
long pr_krest=50;    // ��/����
long pr_guard=100;   // ��/祫
long sod_guard=10;    // ��/���

/* ⥪�騥 業� */
long cur_pr_gold;
long cur_pr_land;
long cur_pr_zerno;
long cur_pr_krest;
long cur_pr_guard;

long for_kar;       // �뤥���� ����� �� ��ࠢ��
long for_xram;      // �뤥���� ����� �� �ࠬ
long abs_sod_guard; // ��᮫�⭠� �⮨����� ᮤ�ঠ��� � ⥪�饬 ����
long run_krest;     // 㡥���� ������ � ⥪�饬 ����
long add_krest;     // த����� ������ � ⥪�饬 ����
long run_guard;     // ������஢��� ���थ�楢 � ⥪�饬 ����
long eat_rat;       // ᮦࠫ� ��ୠ �����
long grab_money;    // �ࠫ ����� ������
long grab_money2;    // �ࠫ ����� ������
long grab_gold;     // �ࠤ��� ����� �� ᮪஢�魨��

/* ��室 ��ୠ �� ������� */
long ed_posev=1;  // �� ��ᥢ �� 1 ��
long ed_eat=3;    // �� ��� �� 1 ���� (krest+guard)

/* ��室 ��ୠ � ⥪�饬 ���� */
long for_posev;  // �� ��ᥢ
long for_eat;    // �� ���

long add_zerno; // ��᮫��� �஦�� � ⥪�饬 ����
long urog=7;    // ����� ��ୠ, �।���/��
long fl_urog;   // 䫠� �஦������
long fl_r;      // 䫠� ॢ���樨
long fl_kar;    // 䫠� ��ࠢ���
long fl_marry;  // 䫠� �������
long fl_end;    // 䫠� ����砭��
long fl_vis;    // 䫠� ������
long fl_mar_war;// 䫠� ����� ��-�� �⪠��
long fl_block;  // 䫠� �������窥᪮� �������

void intro();
void prn_sost(long god);
void new_game();
void prn_rule();

void beg_init()
{
cur_money=money;
cur_gold=gold;
cur_land=land;
cur_zerno=zerno;
cur_krest=krest;
cur_guard=guard;
fl_r=0;
}

long min_loc(long a, long b)
{
 if (a<=b) return a; else return b;
}

long menu(long c, const char *s,int x,int y)
{
int i,l,l2;
char ss[10][255];
char ch;
l=0;
for (i=0; i<c; i++)
 {
  while (s[l]!=39) l++;
  l++;
  l2=0;
  while (s[l]!=39) {ss[i][l2]=s[l]; l++; l2++; }
  ss[i][l2]=0;
  l++;
 }
for (i=0; i<c; i++)
 {
  gotoxy(x,y+i);
  printf("%i. %s.",i+1,ss[i]);
 }
do
 {
  ch=getch();
 }
while ((ch<49)||(ch>48+c));
return ch-48;
}

void main(int argc,char *argv[])
{
long n;
randomize();
textcolor(7);
if ((argc<=1)||(stricmp(argv[1],"no")!=0)) intro();
do
 {
  clrscr();
  n=menu(3,"'����� ���' '������' '��室'",33,11);
  if (n==1) new_game();
  if (n==2) prn_rule();
 }
while (n!=3);
clrscr();
}

void prn_sost(long god)
{
if (fl_end==1)
 printf("\n                   ����ﭨ� ���� ��� ��᫥ %li ��� �ࠢ�����.",god);
else
 printf("\n                   ����ﭨ� ���� ��� �� %li-� ��� �ࠢ�����.",god);
printf("\n����筮��� � �����: %li ��.",cur_money);
printf("\n�����������������������������ͻ");
printf("\n�    ��������    �   ������   �");
printf("\n�����������������������������͹");
printf("\n� �����, ��     � %-10li �",cur_gold);
printf("\n� �����, ��      � %-10li �",cur_land);
printf("\n� ��୮, ⮭�    � %-10li �",cur_zerno);
printf("\n� �����ﭥ, ��� � %-10li �",cur_krest);
printf("\n� ���न�, 祫.  � %-10li �",cur_guard);
printf("\n�����������������������������ͼ");
}

long get_choice()
{
char ch;
long n;
do
 {
  ch=getch();
 }
while ((ch!='y')&&(ch!='Y')&&(ch!='n')&&(ch!='N'));
if ((ch=='y')||(ch=='Y')) n=1;
else n=0;
if (n==1) printf("��"); else printf("���");
return n;
}

long get_chislo()
{
char s[255];
do
 {
 scanf("%s",s);
 }
while ((atol(s)<=0)&&(s[0]!='0'));
return atol(s);
}

long check_enter(long v_old,long v_new)
{
while (v_new>v_old)
 {
  printf("\n� ��� �⮫쪮 ����. ������ ����: ");
  v_new=get_chislo();
 }
return v_new;
}

void visir_message()
{
printf("\n\n��� ������⢮, �ਡ� ������ ������ � ��������.");
printf("\n������ ᮮ�頥�:");
printf("\n�������� ���न� �� ���� ��� ��⠢��� %li �㡫��.",abs_sod_guard);
switch (fl_urog)
 {
  case 0:
   printf("\n���譠� ����� ��ࠧ��� ��ᥢ�. �祭� ���஦���� ���.");
   printf("\n���࠭� �ᥣ� %li ⮭� ��ୠ.",add_zerno);
   break;
  case 1:
   printf("\n�஦������� �뫠 ������. ���࠭� %li ⮭� ��ୠ.",add_zerno);
   break;
  case 2:
   printf("\n�।��� �� �஦������ ���.");
   printf("\n��� �����ﭥ ᮡࠫ� %li ⮭� ��ୠ.",add_zerno);
   break;
  case 3:
   printf("\n�஦���� ���. ���࠭� %li ⮭� ��ୠ.",add_zerno);
   break;
  case 4:
   printf("\n�஫��訥�� ���६� ����� ���ᯥ稫� ��������� ��᮪�� �஦��.");
   printf("\n������ ������� �� ��ୠ - ᮡ࠭� %li ⮭�!",add_zerno);
   break;
 }
if (eat_rat>0)
 printf("\n����㯭�� 堫�⭮���! ����� ᮦࠫ� %li ⮭� ��ୠ!",eat_rat);
if (add_krest>0)
 printf("\n��᫮ ���� ��������� 㢥��稫���. �������� %li ��⥩.",add_krest);
if (run_krest!=-1)
 printf("\n��訬 �����ﭠ� �� 墠⠥� �����. ������� %li 祫����.",run_krest);
if (run_guard!=-1)
 {
  printf("\n�� 墠⨫� ����� �� �믫��� ��������� �������⢨� ��襩 ���न�.");
  printf("\n������஢��� %li ᮫���.",run_guard);
 }
if (grab_gold>0)
 printf("\n�������! �� ᮪஢�魨�� ���饭� %li �� �����!",grab_gold);
if (grab_money>0)
 printf("\n�ࠦ�! ������ ���⨫ %li ��. � �����!..",grab_money);
}

void make_price()
{
cur_pr_gold=((pr_gold*75)/100) + (random(50)*pr_gold/100);
cur_pr_land=((pr_land*75)/100) + (random(50)*pr_land/100);
cur_pr_zerno=((pr_zerno*75)/100) + (random(50)*pr_zerno/100);
cur_pr_krest=((pr_krest*75)/100) + (random(50)*pr_krest/100);
cur_pr_guard=((pr_guard*75)/100) + (random(50)*pr_guard/100);
}

void prn_birge()
{
double f;
printf("����筮��� � �����: %li ��.",cur_money);
printf("\n�������������������������������������������������������������ͻ");
printf("\n�    ��������    �    ������    � ������ 業� � ����騩 ���� �");
printf("\n�������������������������������������������������������������͹");
f=cur_pr_gold*100/pr_gold;
printf("\n� �����, ��     � %-12li � %-12li � %5.1lf%%       �", cur_gold, cur_pr_gold, f);
f=cur_pr_land*100/pr_land;
printf("\n� �����, ��      � %-12li � %-12li � %5.1lf%%       �", cur_land, cur_pr_land, f);
f=cur_pr_zerno*100/pr_zerno;
printf("\n� ��୮, ⮭�    � %-12li � %-12li � %5.1lf%%       �", cur_zerno, cur_pr_zerno, f);
f=cur_pr_krest*100/pr_krest;
printf("\n� �����ﭥ, ��� � %-12li � %-12li � %5.1lf%%       �", cur_krest, cur_pr_krest, f);
f=cur_pr_guard*100/pr_guard;
printf("\n� ���न�, 祫.  � %-12li � %-12li � %5.1lf%%       �", cur_guard, cur_pr_guard, f);
printf("\n�������������������������������������������������������������ͼ");
}

void torgovla()
{
long n,nn,nn2;
long cur;
char ch;
make_price();
do
 {
  clrscr();
  prn_birge();
  printf("\n\n�롥�� ⮢��, � ����� �஢����� ����樨:");
  nn=menu(6,"'�����' '�����' '��୮' '�����ﭥ' '���न�' '��室 � ��ন'",1,13);
  if (nn!=6)
   {
    printf("\n\n�롥�� ⨯ ����権");
    switch (nn)
     {
      case 1: printf(" � ����⮬: "); break;
      case 2: printf(" � ������: "); break;
      case 3: printf(" � ��୮�: "); break;
      case 4: printf(" � �����ﭠ��: "); break;
      case 5: printf(" � ���न��: "); break;
     }
    nn2=menu(2,"'���㯠��' '�த�����'",1,21);
   }
  switch (nn)
   {
    case 1:
     if (nn2==1)
      {
       printf("\n\n����쪮 �����ࠬ��� ����� ������ �㯨��: ");
       cur=get_chislo();
       if (cur*cur_pr_gold>cur_money)
        {
         printf("\n� ��� �� 墠⠥� ����� �⮡� ������� ���㯪�!");
         ch=getch(); if (ch==0) ch=getch();
        }
       else
        {
         cur_gold+=cur;
         cur_money-=cur*cur_pr_gold;
        }
      }
     else
      {
       printf("\n\n����쪮 �����ࠬ��� ����� ������ �த���: ");
       cur=get_chislo();
       cur=check_enter(cur_gold,cur);
       cur_gold-=cur;
       cur_money+=cur*cur_pr_gold;
      }
     break;
    case 2:
     if (nn2==1)
      {
       printf("\n\n����쪮 ����஢ ����� ������ �㯨��: ");
       cur=get_chislo();
       if (cur*cur_pr_land>cur_money)
        {
         printf("\n� ��� �� 墠⠥� ����� �⮡� ������� ���㯪�!");
         ch=getch(); if (ch==0) ch=getch();
        }
       else
        {
         cur_land+=cur;
         cur_money-=cur*cur_pr_land;
        }
      }
     else
      {
       printf("\n\n����쪮 ����஢ ����� ������ �த���: ");
       cur=get_chislo();
       cur=check_enter(cur_land,cur);
       cur_land-=cur;
       cur_money+=cur*cur_pr_land;
      }
     break;
    case 3:
     if (nn2==1)
      {
       printf("\n\n����쪮 ⮭� ��ୠ ������ �㯨��: ");
       cur=get_chislo();
       if (cur*cur_pr_zerno>cur_money)
        {
         printf("\n� ��� �� 墠⠥� ����� �⮡� ������� ���㯪�!");
         ch=getch(); if (ch==0) ch=getch();
        }
       else
        {
         cur_zerno+=cur;
         cur_money-=cur*cur_pr_zerno;
        }
      }
     else
      {
       printf("\n\n����쪮 ⮭� ��ୠ ������ �த���: ");
       cur=get_chislo();
       cur=check_enter(cur_zerno,cur);
       cur_zerno-=cur;
       cur_money+=cur*cur_pr_zerno;
      }
     break;
    case 4:
     if (nn2==1)
      {
       printf("\n\n����쪮 ��� ������ ������ �㯨��: ");
       cur=get_chislo();
       if (cur*cur_pr_krest>cur_money)
        {
         printf("\n� ��� �� 墠⠥� ����� �⮡� ������� ���㯪�!");
         ch=getch(); if (ch==0) ch=getch();
        }
       else
        {
         cur_krest+=cur;
         cur_money-=cur*cur_pr_krest;
        }
      }
     else
      {
       printf("\n\n����쪮 ��� ������ ������ �த���: ");
       cur=get_chislo();
       cur=check_enter(cur_krest,cur);
       cur_krest-=cur;
       cur_money+=cur*cur_pr_krest;
      }
     break;
    case 5:
     if (nn2==1)
      {
       printf("\n\n����쪮 ���थ�楢 ������ ������: ");
       cur=get_chislo();
       if (cur*cur_pr_guard>cur_money)
        {
         printf("\n� ��� �� 墠⠥� ����� �⮡� ������� ���㯪�!");
         ch=getch(); if (ch==0) ch=getch();
        }
       else
        {
         cur_guard+=cur;
         cur_money-=cur*cur_pr_guard;
        }
      }
     else
      {
       printf("\n\n����쪮 ���थ�楢 ������ �த���: ");
       cur=get_chislo();
       cur=check_enter(cur_guard,cur);
       cur_guard-=cur;
       cur_money+=cur*cur_pr_guard;
      }
     break;
   }
 }
while (nn!=6);
}

void choice_zerno()
{
long n;
long cur;
printf("\n\n������ ᠬ� ��।����� ��室 ��ୠ (y/n): ");
n=get_choice();
if (n==0)
 {
  for_eat=(cur_krest+cur_guard)*ed_eat;
  for_posev=min_loc(cur_land,cur_krest)*ed_posev;
  if ((for_eat+for_posev)<=cur_zerno)
   {
    cur_zerno=cur_zerno-for_eat-for_posev;
    printf("\n\n�뤥���� ��ୠ: �� ��� - %li ⮭�, �� ��ᥢ - %li ⮭�.",for_eat,for_posev);
    printf("\n��⠢訩�� ����� � ������: %li ⮭�.",cur_zerno);
   }
  else
   {
    printf("\n\n�� ���� ᠬ����⥫쭮 ��।����� ��୮.");
    printf("\n�� 墠⠥� ��ୠ �� ��ᥢ � ��� �� ������ ��ଥ.");
    printf("\n��������, ��।���� ��୮ ��筮.");
    n=1;
   }
 }
if (n==1)
 {
  printf("\n���������, ��� ���ﭨ� ᥩ�� ��⠢���:");
  printf("\n����� - %li ��, �����ﭥ - %li ���, ���न� - %li 祫.",cur_land,cur_krest,cur_guard);
  printf("\n����� ��ୠ � ������ - %li ⮭�.",cur_zerno);
  printf("\n\n������ ��室 ��ୠ �� ���: ");
  cur=get_chislo();
  cur=check_enter(cur_zerno,cur);
  for_eat=cur;
  cur_zerno-=cur;
  printf("\n������ ��室 ��ୠ �� ��ᥢ: ");
  cur=get_chislo();
  cur=check_enter(cur_zerno,cur);
  for_posev=cur;
  cur_zerno-=cur;
  printf("\n��⠢訩�� ����� � ������: %li ⮭�.",cur_zerno);
 }
}

/* 0 - ���譠� �����, 1 - ���宭쪠� �஦�������, 2 - �।��� �஦�������
   3 - ���� �஦�������, 4 - ��������� �����த�� ��� */

long make_turn()
{
long n;
long a,b;
double f,f1,f2,f3;
// ��ࠡ�⪠ (�����ﭥ+���न�) - ��୮
f1=for_eat;
f2=ed_eat;
f3=cur_krest+cur_guard;
f=(f1/f2)/f3;
printf("\n\n��ଠ �த�⮢ �� ��� �� 1 祫����� ��⠢��� %.1lf%% �� ����室����.",f*100);
if (f>=1.) printf("\n��த ������� ⠪�� 饤�� �ࠢ��⥬.");
if ((f<1.)&&(f>=0.7)) printf("\n��ନ� ��த ������, �� � ������ ���������...");
if ((f<0.7)&&(f>=0.4))
 {
  n=random(100);
  if (n<100-(f*100))
   {
    printf("\n�� ����ࠫ���... ��த �� �⠫ �௥�� ⠪�� 㭨����� � ᢥ� ���!!!");
    printf("\n�� ������� ����� ᢮� ��த �� ���������!!!");
    return 1;
   }
  else
   {
    printf("\n���������⢮ ���� १�� ����᫮. �� ᨫ쭮 ����...");
    printf("\n���쪮 ��砩 ᯠ� ��� � ��� ࠧ �� ���������...");
   }
 }
if (f<0.4)
 {
  printf("\n�� �� ��, ����������?!! ��� ����� ������� ᢮� ��த!..");
  printf("\n�த��� �� ��譨� ������, �����, �᫨ �ப�ନ�� �� �����...");
  printf("\n����⢥���, 㬨��騩 �� ������ ��த ᢥ� ⠪��� �࠭�...");
  printf("\n������ ���������!!!");
  return 1;
 }
// ��ࠡ�⪠ �஦��
fl_urog=random(5);
a=min_loc(cur_krest,cur_land);
b=min_loc(a,for_posev);
add_zerno=(fl_urog*2+3)*b;
cur_zerno+=add_zerno;
// ��ࠡ�⪠ ����
n=random(100);
if (n<20)
 {
  eat_rat=(random(20)*cur_zerno)/100;
  cur_zerno-=eat_rat;
 }
else eat_rat=-1;
// ��ࠡ�⪠ ����� - �����ﭥ
if (cur_krest>cur_land)
 {
  run_krest=random(cur_krest-cur_land);
  cur_krest-=run_krest;
 }
else run_krest=-1;
n=random(10)+6;
add_krest=(cur_krest*n)/100;
cur_krest+=add_krest;
// ��ࠡ�⪠ ���न� - ���죨
abs_sod_guard=(cur_guard+1)*sod_guard;
if (abs_sod_guard>cur_money)
 {
  n=random(10)+6;
  run_guard=(cur_guard*n)/100;
  cur_guard-=run_guard;
  abs_sod_guard=(cur_guard+1)*sod_guard;
  if (abs_sod_guard>cur_money) abs_sod_guard=cur_money;
 }
else
 run_guard=-1;
cur_money-=abs_sod_guard;
// ��ࠡ�⪠ ���饭�� �����
if (cur_gold>0)
 {
  n=random(100);
  if (n<20)
   {
    grab_gold=(random(25)*cur_gold)/100;
    cur_gold-=grab_gold;
   }
  else grab_gold=-1;
 }
else grab_gold=-1;
// ��ࠡ�⪠ ������ - ���죨
if (cur_money>0)
 {
  n=random(100);
  if (n<10)
   {
    grab_money=(random(25)*cur_money)/100;
    grab_money2=grab_money;
    cur_money-=grab_money;
    fl_vis=1;
   }
  else grab_money=-1;
 }
else grab_money=-1;
return 0;
}

void prn_ochki(long i)
{
printf("\n���죨 - %li; ",cur_money/1000);
printf("����� - %li; ",cur_gold*2);
printf("����� - %li; ",cur_land/5);
printf("��୮ - %li; ",cur_zerno/100);
printf("\n�����ﭥ - %li; ",cur_krest/20);
printf("���न� - %li; ",cur_guard/10);
printf("���� �ࠬ� - %li; ",build_xram*200);
printf("�६� �ࠢ����� - %li.",i*10);
}

long make_ochki(long i)
{
ochki=0;
ochki+=(cur_money/1000);
ochki+=(cur_gold*2);
ochki+=(cur_land/5);
ochki+=(cur_zerno/100);
ochki+=(cur_krest/20);
ochki+=(cur_guard/10);
ochki+=build_xram*200;
ochki+=i*10;
return ochki;
}

long snarad_kar()
{
long n;
long cur;
printf("\n\n�����᪨� �㯥� �।������ ᭠�廊�� ��ࠢ��. �� ᮣ���� (y/n): ");
n=get_choice();
if (n==0) return 0;
printf("\n� ����� - %li ��, ᪮�쪮 �� ��ࠢ��: ",cur_money);
cur=get_chislo();
cur=check_enter(cur_money,cur);
printf("��ࠢ�� ��ࠢ���� �� ��-������ ������...");
cur_money-=cur;
for_kar=cur;
return 1;
}

void grabeg_kar()
{
long n,grab;
n=random(100);
if (n<5)
 {
  printf("\n\n�ந��諮 ��! ��� ��ࠢ�� ��������� ࠧ�ࠡ��� �����⠬�!!!");
  fl_kar=0;
  for_kar=0;
 }
else
 {
  n=random(40);
  grab=(for_kar*n)/100;
  printf("\n\n��������, ��! ��� ��ࠢ�� ��ࠡ��� �����⠬� �� �㬬� %li ��.!!!",grab);
  for_kar-=grab;
 }
}

void pribil_kar()
{
long prib;
prib=for_kar*6;
printf("\n\n������ ��� ��ࠢ��! ����祭� �ਡ뫨 �� �㬬� %li ��.!",prib);
cur_money+=prib;
}

void mitropolit()
{
long cur,nn;
double f,f1,f2;
printf("\n\n���ய���� ��襣� ���㤠��⢠ ���� ����� �� ���� �ࠬ.");
printf("\n����쪮 �뤥��� (� ����� %li ��.): ",cur_money);
cur=get_chislo();
cur=check_enter(cur_money,cur);
for_xram+=cur;
f1=cur; f2=cur_money;
f=f1/f2; f*=100;
cur_money-=cur;
if (f<=1)
 printf("\n�� ��, ��ᬥ堥����?! ���!!! �� ⢮� �������� �� ᣮ��� � ���!");
if ((f>1)&&(f<=10))
 printf("\n��������, �� ���! ����� �� ���� ⠪�� �����, �� ᬥ��� ���!");
if ((f>10)&&(f<=20))
 printf("\n�� ᫨誮�-� 饤�� ⢮� �ਭ�襭��, �� ���. ����� �뫮 ���� � �������.");
if ((f>20)&&(f<=30))
 printf("\n�� �, ᯠᨡ� � �� �⮬. ��� �ਭ�襭�� ������ �� ����㣮���� ����.");
if ((f>30)&&(f<=50))
 printf("\n��������� ⥡�, �� ���. ���� 饤���� �㤥� �業��� �� ���⮨����.");
if (f>50)
 printf("\n�� ��� �ࠬ�� ��࠭� ���� ������ �� ᫠�� ��ண� � 饤ண� ��஫�!");
nn=for_xram/100000;
if (nn>0)
 {
  for_xram-=nn*100000;
  build_xram+=nn;
  if (nn==1)
   printf("\n���������� ���� �ࠬ.");
  if ((nn>=2)&&(nn<=4))
   printf("\n���������� %li ����� �ࠬ�.",nn);
  if (nn>=5)
   printf("\n���������� %li ����� �ࠬ��.",nn);
 }
}

void nasledstvo()
{
long cur;
long n;
printf("\n\n���� ��� ���쭨� த�⢥����. �� ����稫� ��᫥��⢮ � ࠧ���:");
n=random(90)+10; cur=cur_money*n/100; cur_money+=cur;
printf("\n���죨 - %li ��.",cur);
n=random(90)+10; cur=cur_gold*n/100; cur_gold+=cur;
printf("\n����� - %li ��.",cur);
n=random(90)+10; cur=cur_land*n/100; cur_land+=cur;
printf("\n����� - %li ��.",cur);
n=random(90)+10; cur=cur_zerno*n/100; cur_zerno+=cur;
printf("\n��୮ - %li ⮭�.",cur);
n=random(90)+10; cur=cur_krest*n/100; cur_krest+=cur;
printf("\n�����ﭥ - %li ���.",cur);
n=random(90)+10; cur=cur_guard*n/100; cur_guard+=cur;
printf("\n������� - %li 祫.",cur);
}

void poimali_visir()
{
long cur;
printf("\n\n��� ������ ������� ᡥ���襣� ������!");
printf("\n� ���� ����᪮���� �� �����⢮, � ��� ᠬ��� ��ᠤ��� �� ���!");
cur=(random(50)+50)*grab_money2/100;
printf("\n� ����� �����饭� %li ��.",cur);
cur_money+=cur;
fl_vis=0;
}

void sosed_marry()
{
long n;
long cur;
long prid_money,prid_gold,prid_land,prid_zerno,prid_krest,prid_guard;
printf("\n\n��ᥤ��� ��஫� ᢠ⠥� �� ��� ᢮� ����.");
printf("\n� �ਤ����� �� �।������:");
n=random(90)+10; cur=cur_money*n/100; prid_money=cur;
printf("\n���죨 - %li ��.",cur);
n=random(90)+10; cur=cur_gold*n/100; prid_gold=cur;
printf("\n����� - %li ��.",cur);
n=random(90)+10; cur=cur_land*n/100; prid_land=cur;
printf("\n����� - %li ��.",cur);
n=random(90)+10; cur=cur_zerno*n/100; prid_zerno=cur;
printf("\n��୮ - %li ⮭�.",cur);
n=random(90)+10; cur=cur_krest*n/100; prid_krest=cur;
printf("\n�����ﭥ - %li ���.",cur);
n=random(90)+10; cur=cur_guard*n/100; prid_guard=cur;
printf("\n������� - %li 祫.",cur);
printf("\n\n�� ᮣ���� (y/n): ");
n=get_choice();
if (n==1)
 {
  cur=(random(40)+20)*cur_money/100;
  printf("\n\n����ࠢ���. �� ᢠ����� ��� ����祭� %li ��.",cur);
  cur_money-=cur;
  cur_money+=prid_money; cur_gold+=prid_gold; cur_land+=prid_land;
  cur_zerno+=prid_zerno; cur_krest+=prid_krest; cur_guard+=prid_guard;
  fl_marry=1;
 }
else
 {
  printf("\n\n�� ⠪?!! �� �७��ॣ��� ���� �।��������??! ��⮢���� � �����!");
  fl_mar_war=1;
 }
}

void begin_war()
{
char ch;
long cur,ras;
long your_men,enemy_men;
long n,victory;
cur=random((cur_guard+cur_krest)*2);
enemy_men=cur;
your_men=cur_guard;
ras=cur-(50*cur/100)+random(cur);
printf("\n�������� ������ � �।���������� �᫥����� ���� �ࠣ�: %li ᮫���.",ras);
printf("\n��� ᨫ�: %li ᮫���. ����� ���������� ������ (y/n)? ",your_men);
n=get_choice();
if (n==1)
 {
  cur=(random(50)+50)*cur_krest/100;
  printf("\n������������ %li 祫����. � ��த� ���� ���������⢮!",cur);
  your_men+=cur;
 }
printf("\n���� ����������� ����࡮���� ��������� �� �६� �⮩ �����.");
printf("\n���� ������� �⮨� 100 �㡫��. �㤥� ��࡮���� (y/n)? ");
n=get_choice();
if (n==1)
 {
  printf("\n����쪮 ��������� ��� ������ (� ����� - %li ��.): ",cur_money);
  cur=get_chislo();
  cur=check_enter(cur_money/100,cur);
  your_men+=cur;
  cur_money-=cur*100;
 }
else printf("\n");
printf("\n��। ��⢮� ���᭨���� �筮� �᫮ ���� ��⨢����: %li ᮫���.",enemy_men);
printf("\n��� ���᪠ ��⠢���� %li ᮫���.",your_men);
printf("\n������ ���� ������� ��� ��砫� �ࠦ����...");
ch=getch(); if (ch==0) ch=getch();
victory=0;
n=random(enemy_men+your_men*2);
if (n<=your_men*2) victory=1;
if (victory==1)
 {
  printf("\n\n�� ��������! ��� �ନ� ��墠⨫� ��䥨:");
  n=random(90)+10; cur=cur_money*n/100; cur_money+=cur;
  printf("\n���죨 - %li ��.",cur);
  n=random(90)+10; cur=cur_gold*n/100; cur_gold+=cur;
  printf("\n����� - %li ��.",cur);
  n=random(90)+10; cur=cur_land*n/100; cur_land+=cur;
  printf("\n����� - %li ��.",cur);
  n=random(90)+10; cur=cur_zerno*n/100; cur_zerno+=cur;
  printf("\n��୮ - %li ⮭�.",cur);
  n=random(90)+10; cur=cur_krest*n/100; cur_krest+=cur;
  printf("\n�����ﭥ - %li ���.",cur);
 }
else
 {
  printf("\n\n�� �ந�ࠫ�... ��� ���� � �⮩ �����:");
  n=random(90)+10; cur=cur_money*n/100; cur_money-=cur;
  printf("\n���죨 - %li ��.",cur);
  n=random(90)+10; cur=cur_gold*n/100; cur_gold-=cur;
  printf("\n����� - %li ��.",cur);
  n=random(90)+10; cur=cur_land*n/100; cur_land-=cur;
  printf("\n����� - %li ��.",cur);
  n=random(90)+10; cur=cur_zerno*n/100; cur_zerno-=cur;
  printf("\n��୮ - %li ⮭�.",cur);
  n=random(90)+10; cur=cur_krest*n/100; cur_krest-=cur;
  printf("\n�����ﭥ - %li ���.",cur);
  n=random(90)+10; cur=cur_guard*n/100; cur_guard-=cur;
  printf("\n������� - %li 祫.",cur);
 }
}

void rodilsa_sin()
{
long cur;
printf("\n\n� ��� த���� ��! ����ࠢ���! ��� ������� �� 㣠᭥� � �����!");
cur=(random(40)+20)*cur_money/100;
printf("\n�� �ࠧ����� ������ �� ���� ஦����� �뭠 ����祭� %li ��.",cur);
cur_money-=cur;
}

void dead_wife()
{
long cur;
long n;
printf("\n\n�ਡ� ����� �� ��஫���. ������� (y/n)? ");
n=get_choice();
if (n==0)
 printf("\n���� �� � �� �ਭ﫨 ����, �� ��砫쭠� ����� �� ࠢ�� ��諠 �� ���.");
printf("\n������� �������! ���ૠ ��஫���! �������訩 ������ �����襭!");
cur=(random(40)+20)*cur_money/100;
printf("\n�� ���஭� ��஫��� ����祭� %li ��.",cur);
cur_money-=cur;
fl_marry=0;
}

void koroleva_prosit()
{
long n,cur;
char ch;
n=random(100);
if (n<15)
 {
  printf("\n\n�ਡ� ����� �� ��஫���. ������� (y/n)? ");
  n=get_choice();
  if (n==0) return;
  cur=(random(30)+1)*cur_money/100;
  printf("\n��஫��� ���� %li ��. �� ����� �����. �뤥���� �।�⢠ (y/n)? ",cur);
  n=get_choice();
  if (n==1)
   {
    printf("\n��஫��� ��������� ��� /��筮 � ����� �����... :-) /");
    cur_money-=cur;
   }
  else
   printf("\n��஫��� ����� �� ��� ���������... ������ ��� ����� �� ������...");
  printf("\n\n������ ���� �������...");
  ch=getch(); if (ch==0) ch=getch();
 }
else
 {
  n=random(100);
  if (n<15)
   {
    printf("\n\n�ਡ� ����� �� ��஫���. ������� (y/n)? ");
    n=get_choice();
    if (n==0) return;
    cur=(random(30)+1)*cur_money/100;
    printf("\n\n��஫��� ���� %li ��., �⮡� ���ந�� ���. �뤥���� �।�⢠ (y/n)? ",cur);
    n=get_choice();
    if (n==1)
     {
      printf("\n��஫��� ��������� ��� /��筮 � ����� �����... :-) /");
      cur_money-=cur;
     }
    else
     printf("\n��஫��� �� ��� ���������... ���� � �� �祭� ᨫ쭮, �� �� ⠪�...");
    printf("\n\n������ ���� �������...");
    ch=getch(); if (ch==0) ch=getch();
   }
 }
}

long shaman()
{
long cur,n,n2,fl;
printf("\n����� 蠬�� ������ �뫥��� ��� (� ����⭮���� 20%%...)");
cur=(random(40)+1)*cur_money/100;
printf("\n�� �� �� �� �ॡ�� �������� ��襣� ����� � %li ��.",cur);
printf("\n�� ᮣ���� (y/n)? ");
n=get_choice();
if (n==1)
 {
  cur_money-=cur;
  cur_gold-=cur_gold/2;
  n2=random(100);
  if (n2<20)
   {
    printf("\n\n�������⢮ 蠬��� �������! �� �매�஢���!");
    fl=0;
   }
  else
   {
    printf("\n\n����� ��祬 �� ᬮ� ������ ���... ��஫� ����!!!");
    fl=1;
   }
 }
else
 {
  n2=random(100);
  if (n2<5)
   {
    printf("\n\n���稫��� ����! �� �������� ������� � ��⠫� � ᬥ�⭮�� ���!");
    fl=0;
   }
  else
   {
    printf("\n\n������� �������� ���... ��஫� ����!!!");
    fl=1;
   }
 }
return fl;
}

long korol_bolen(long i)
{
long fl,n,n2,cur;
cur=(random(30)+1)*cur_money/100;
printf("\n\n�� ��������! �� ��祭�� ������ ���� %li �㡫��.",cur);
printf("\n�� ����� �매�஢��� ᠬ�, �� ����� � �� �매�஢���...");
printf("\n�㤥� ������� (y/n)? ");
n=get_choice();
if (n==1)
 {
  cur_money-=cur;
  n2=random(100);
  if (n2<5)
   {
    printf("\n��祭�� �� ���� १���⮢. �� ��ᬥ��...");
    fl=shaman();
   }
  else
   {
    printf("\n��祭�� �������, �� ���������筮 �매�஢���...");
    fl=0;
   }
 }
else
 {
  n2=random(100);
  if (n2<i*2)
   {
    printf("\n� �� ��� �।�०���! ������� �����ਫ���, �� ��ᬥ��!");
    fl=shaman();
   }
  else
   {
    printf("\n�� ���������筮 ��楫����� ᠬ�...");
    fl=0;
   }
 }
return fl;
}

void new_game()
{
long i,n;
char ch;
long cur;
clrscr();
beg_init();
i=1;
fl_kar=0; fl_marry=0; fl_end=0; fl_vis=0; build_xram=0; for_xram=0;

do
 {
  clrscr();

  prn_sost(i);
  if (i>1) visir_message();

  if (fl_kar==5)
   {
    pribil_kar();
    fl_kar=0;
   }

  n=random(100);
  if (n<25)
   {
    printf("\n\n����㭠த�� �ਧ��! ��࣮��� ����������!");
    printf("\n��襬� ���㤠���� ������ ��������᪠� �������!");
    fl_block=1;
    printf("\n\n������ ���� �������...");
    ch=getch(); if (ch==0) ch=getch();
   }
  else
   {
    printf("\n\n������ �࣮���� �� ��থ (y/n)? ");
    n=get_choice();
    if (n==1) torgovla();
    fl_block=0;
   }

  if (fl_kar==0)
   {
    n=random(100);
    if (n<25) fl_kar=snarad_kar();
   }

  if (fl_kar>1)
   {
    n=random(100);
    if (n<20) grabeg_kar();
   }

  if (fl_kar>0) fl_kar++;

  n=random(100);
  if (n<20)
   {
    mitropolit();
    printf("\n\n������ ���� �������...");
    ch=getch(); if (ch==0) ch=getch();
   }

  if (fl_mar_war)
   {
    printf("\n\n���������� �⪠��� �������� �� ��� ��窥, �ᥤ��� ��஫� ��砫 �����!");
    begin_war();
    printf("\n\n������ ���� �������...");
    ch=getch(); if (ch==0) ch=getch();
    fl_mar_war=0;
   }

  if (cur_guard<100)
   {
    n=random(100);
    if (n>cur_guard)
     {
      printf("\n\n��ᥤ��� ��஫�, ���� �����᫥������ ���� ����, ����� ��� �����!");
      begin_war();
      printf("\n\n������ ���� �������...");
      ch=getch(); if (ch==0) ch=getch();
     }
   }
  else
   {
    n=random(100);
    if (n<30)
     {
      printf("\n\n���� ����������� ����� ����� ������ �� �ᥤ��. �����? ");
      n=get_choice();
      if (n==1)
       {
        begin_war();
        printf("\n\n������ ���� �������...");
        ch=getch(); if (ch==0) ch=getch();
       }
     }
   }

  if (fl_vis==1)
   {
    n=random(100);
    if (n<15)
     {
      poimali_visir();
      printf("\n\n������ ���� �������...");
      ch=getch(); if (ch==0) ch=getch();
     }
   }

  n=random(100);
  if (n<10)
   {
    nasledstvo();
    printf("\n\n������ ���� �������...");
    ch=getch(); if (ch==0) ch=getch();
   }

  if (fl_marry==1)
   {
    n=random(100);
    if (n<10)
     {
      rodilsa_sin();
      printf("\n\n������ ���� �������...");
      ch=getch(); if (ch==0) ch=getch();
     }
   }

  if (fl_marry==0)
   {
    n=random(100);
    if (n<15)
     {
      sosed_marry();
      printf("\n\n������ ���� �������...");
      ch=getch(); if (ch==0) ch=getch();
     }
   }

  if (fl_marry==1)
   {
    n=random(100);
    if (n<10)
     {
      dead_wife();
      printf("\n\n������ ���� �������...");
      ch=getch(); if (ch==0) ch=getch();
     }
   }

  if (fl_marry==1) koroleva_prosit();

  n=random(100);
  if (n<i*2)
   {
    fl_end=korol_bolen(i);
    printf("\n\n������ ���� �������...");
    ch=getch(); if (ch==0) ch=getch();
    if (fl_end) break;
   }

  choice_zerno();

  fl_r=make_turn();
  if (fl_r==1)
   {
    ch=getch(); if (ch==0) ch=getch();
    fl_end=1;
    break;
   }

  printf("\n\n�㤥� �ࠢ��� � ᫥���饬 ���� (y/n)? ");
  n=get_choice();
  if (n==0) { fl_end=1; break; }

  printf("\n\n�㤥� ���ࠨ���� ���������� ��� (y/n)? ");
  n=get_choice();
   if (n==1)
   {
    printf("\n����쪮 ���� �� ��� (� ����� - %li ��.): ",cur_money);
    cur=get_chislo();
    cur=check_enter(cur_money,cur);
    cur_money-=cur;
    if (cur==0)
     {
      printf("� �� ����, �� ���ࠨ���� ��� ��� ���?! �� �� �� �㬬� ⠪�� - 0 �㡫��?!");
      printf("\n�᫨ ����� �����, � ᪠��� '���' �ࠧ� � �� ���� ��� �����!!!");
     }
    else
     {
      if (fl_marry>0) printf("��஫��� ��������� ���.");
      else printf("�ਤ���� ���������� ���.");
     }
   }

  i++;
  printf("\n\n������ ���� �������...");
  ch=getch(); if (ch==0) ch=getch();
 }
while (i<=50);

if (i>50) i=50;
clrscr();
fl_end=1;
if (fl_r==0) printf("��� �ࠢ����� �����訫���...\n");
else
 {
  printf("�������騩 ��த ������� � ᢥ࣭� ��ࠤ����� �ࠢ�⥫�!!!");
  printf("\n����ࠢ��� ���, ��⥭쪠, � ����������, �-�...\n");
 }
prn_sost(i);
printf("\n\n�� ��� ���ﭨ� ��� ������ ᫥���饥 ������⢮ �窮�:");
ochki=make_ochki(i);
prn_ochki(i);
printf("\n���� �㬬� ���� �窮�: %li",ochki);
printf("\n\n�� �� �... ����ࠢ��� � �ᯥ�� (?) ����砭��� ����.");
if ((ochki>=0)&&(ochki<=100) )
 printf("\nP.S. ��� �� ���� ��ᥩ ����... ����� ���� ������...");
if ((ochki>100)&&(ochki<=300))
 printf("\nP.S. ��� ����窠 - ᮩ���... ����, ����筮, �������...");
if ((ochki>300)&&(ochki<=500))
 printf("\nP.S. ��, �� 㦥 ���-��... �㤮-�����, �� �����...");
if ((ochki>500)&&(ochki<=1000))
 printf("\nP.S. �� ���, ���-�� 㦥 ����砥���. ��ࠩ��� �����...");
if ((ochki>1000)&&(ochki<=3000))
 printf("\nP.S. ������, ���쬠 ������... ������...");
if ((ochki>3000)&&(ochki<=5000))
 printf("\nP.S. �� �, �����, ����� �� 㬥��... ���쬠 ������⢥���...");
if ((ochki>5000)&&(ochki<=10000))
 printf("\nP.S. ����, �� �������... �� ��, ��⥭쪠, ����ᨮ���...");
if ((ochki>10000)&&(ochki<=100000))
 printf("\nP.S. ���� ��, ��ᯮ��... �� ��, ����, ����!!!");
if (ochki>100000)
 printf("\nP.S. NO pity, NO mercy, NO REGRET!!!!!!!!!!");
ch=getch(); if (ch==0) ch=getch();
}