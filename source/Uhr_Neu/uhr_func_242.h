#include <Arduino.h>

unsigned int matrix[22 ][11] = {                               

  {0,   1,  2,  3,  4,  5,  6,  7,  8,  9, 10},
  {21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11},
  {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32},
  {43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33},
  {44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54},
  {65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55},
  {66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76},
  {87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77},
  {88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98},
  {109,108,107,106,105,104,103,102,101,100,99}, 
  {110,111,112,113,114,115,116,117,118,119,120},
  
  {131,130,129,128,127,126,125,124,123,122,121},
  {132,133,134,135,136,137,138,139,140,141,142},
  {153,152,151,150,149,148,147,146,145,144,143},
  {154,155,156,157,158,159,160,161,162,163,164},
  {175,174,173,172,171,170,169,168,167,166,165},
  {176,177,178,179,180,181,182,183,184,185,186},
  {197,196,195,194,193,192,191,190,189,188,187},
  {198,199,200,201,202,203,204,205,206,207,208},
  {219,218,217,216,215,214,213,112,211,210,209},
  {220,221,222,223,224,225,226,227,228,229,230},
  {241,240,239,238,237,236,235,234,233,232,231},
};
//------------------------------------------------------------------------------

unsigned int smatrix[242] = {                             

   0,   1,  2,  3,  4,  5,  6,  7,  8,  9, 10,
   11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
   22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
   33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43,
   44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54,
   55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65,
   66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76,
   77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87,
   88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98,
   99,100,101,102,103,104,105,106,107,108,109,
   110,111,112,113,114,115,116,117,118,119,120,
   121,122,123,124,125,126,127,128,129,130,131,
   132,133,134,135,136,137,138,139,140,141,142,
   143,144,145,146,147,148,149,150,151,152,153,
   154,155,156,157,158,159,160,161,162,163,164,
   165,166,167,168,169,170,171,172,173,174,175,
   176,177,178,179,180,181,182,183,184,185,186,
   187,188,189,190,191,192,193,194,195,196,197,
   198,199,200,201,202,203,204,205,206,207,208,
   209,210,211,212,213,214,215,216,217,218,219,
   220,221,222,223,224,225,226,227,228,229,230,
   231,232,233,234,235,236,237,238,239,240,241};

//------------------------------------------------------------------------------

unsigned int min_arr[2][4] = {
  {112,  114,  116,  118},              // Minuten LED´s für Zeile
  {112,  114,  116,  118}               // Minuten LED´s für Ecken
};

//------------------------------------------------------------------------------

void es_ist() 
{
  //Es
  led_set(0);
  led_set(1);  
  
  //Ist
  led_set(3);
  led_set(4);
  led_set(5);
}

//------------------------------------------------------------------------------

void viertel()
{ 
  led_set(26);
  led_set(27);
  led_set(28);
  led_set(29);
  led_set(30);
  led_set(31);
  led_set(32);   
} 

//------------------------------------------------------------------------------

void fuenf()
{
  led_set(7);
  led_set(8);
  led_set(9);
  led_set(10);  
}

//------------------------------------------------------------------------------

void zehn()
{
  led_set(18);
  led_set(19);
  led_set(20);
  led_set(21);
}

//------------------------------------------------------------------------------
void zwanzig()
{
  led_set(11);
  led_set(12);
  led_set(13);
  led_set(14);
  led_set(15);  
  led_set(16);
  led_set(17);   
}

//------------------------------------------------------------------------------

void halb()
{  
  led_set(44);
  led_set(45);
  led_set(46);
  led_set(47); 
}

//------------------------------------------------------------------------------

void eins()
{
  led_set(60);
  led_set(61);
  led_set(62);
  led_set(63); 
}

//------------------------------------------------------------------------------

void nach()
{  
  led_set(38);
  led_set(39);
  led_set(40);
  led_set(41);
}

//------------------------------------------------------------------------------

void vor()
{
  led_set(35);
  led_set(36);
  led_set(37); 
}
//------------------------------------------------------------------------------

void uhr()
{
  led_set(100);
  led_set(101);
  led_set(102);
}

//------------------------------------------------------------------------------

void h_ein()
{
  led_set(61);
  led_set(62);
  led_set(63);
}

//------------------------------------------------------------------------------

void h_zwei()
{  
  led_set(62);
  led_set(63);
  led_set(64);
  led_set(65); 
}

//------------------------------------------------------------------------------

void h_drei()
{  
  led_set(67);
  led_set(68);
  led_set(69);
  led_set(70);  
}

//------------------------------------------------------------------------------

void h_vier()
{ 
  led_set(77);
  led_set(78);
  led_set(79);
  led_set(80);  
}

//------------------------------------------------------------------------------

void h_fuenf()
{  
  led_set(73);
  led_set(74);
  led_set(75);
  led_set(76);  
}

//------------------------------------------------------------------------------

void h_sechs()
{
  led_set(104);
  led_set(105);
  led_set(106);
  led_set(107);
  led_set(108);
}

//------------------------------------------------------------------------------

void h_sieben()
{
  led_set(55);
  led_set(56);
  led_set(57);
  led_set(58);
  led_set(59);   
  led_set(60);     
}

//------------------------------------------------------------------------------

void h_acht()
{
  led_set(89);
  led_set(90);
  led_set(91);
  led_set(92);
}

//------------------------------------------------------------------------------

void h_neun()
{
  led_set(81);
  led_set(82);
  led_set(83);
  led_set(84);  
}

//------------------------------------------------------------------------------

void h_zehn()
{
  led_set(93);
  led_set(94);
  led_set(95);
  led_set(96); 
}

//------------------------------------------------------------------------------

void h_elf()
{
  led_set(85);
  led_set(86);
  led_set(87);
}

//------------------------------------------------------------------------------

void h_zwoelf()
{ 
  led_set(49);
  led_set(50);
  led_set(51);
  led_set(52);
  led_set(53);
}

//------------------------------------------------------------------------------
// Wetter
//------------------------------------------------------------------------------

void w_morgen()
{
  led_set(131);
  led_set(130);
  led_set(129);
  led_set(128);
  led_set(127);
  led_set(126);
  }

void w_frueh()
{
  led_set(124);
  led_set(123);
  led_set(122);
  led_set(121);
  }
void w_abend()
{
  led_set(132);
  led_set(133);
  led_set(134);
  led_set(135);
  led_set(136);
}

void w_mittag()
{
  led_set(137);
  led_set(138);
  led_set(139);
  led_set(140);
  led_set(141);
  led_set(142);
}

void w_nacht()
{
  led_set(153);
  led_set(152);
  led_set(151);
  led_set(150);
  led_set(149);
}

void w_schnee()
{
  led_set(148);
  led_set(147);
  led_set(146);
  led_set(145);
  led_set(144);
  led_set(143);
}

void w_klar()
{
  led_set(154);
  led_set(155);
  led_set(156);
  led_set(157);
}

void w_warnung()
{
  led_set(158);
  led_set(159);
  led_set(160);
  led_set(161);
  led_set(162);
  led_set(163);
  led_set(164);
}

void w_regen()
{
  led_set(175);
  led_set(174);
  led_set(173);
  led_set(172);
  led_set(171);
}

void w_wolken()
{
  led_set(170);
  led_set(169);
  led_set(168);
  led_set(167);
  led_set(166);
  led_set(165);
}

void w_gewitter()
{
  led_set(177);
  led_set(178);
  led_set(179);
  led_set(180);
  led_set(181);
  led_set(182);
  led_set(183);
  led_set(184);
}

void w_unter()
{
  led_set(197);
  led_set(196);
  led_set(195);
  led_set(194);
  led_set(193);
}

void w_ueber()
{
  led_set(191);
  led_set(190);
  led_set(189);
  led_set(188);
}

void w_minus()
{
  led_set(199);
  led_set(200);
  led_set(201);
  led_set(202);
  led_set(203);
}

void w_null()
{
  led_set(205);
  led_set(206);
  led_set(207);
  led_set(208);
}

void w_fuenf()
{
  led_set(219);
  led_set(218);
  led_set(217);
  led_set(216);
}

void w_zehn()
{
  led_set(215);
  led_set(214);
  led_set(213);
  led_set(212);
}

void w_und()
{
  led_set(211);
  led_set(210);
  led_set(209);
}

void w_zwanzig()
{
  led_set(222);
  led_set(223);
  led_set(224);
  led_set(225);
  led_set(226);
  led_set(227);
  led_set(228);
}

void w_dreissig()
{
  led_set(241);
  led_set(240);
  led_set(239);
  led_set(238);
  led_set(237);
  led_set(236);
  led_set(235);
}

void w_grad()
{
  led_set(233);
  led_set(232);
}

