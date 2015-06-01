/**
 * @file gamelogic.cc
 * @brief 
 * @author H.M.Yang, hmyang07@gmail.com
 * @version v1.0
 * @date 05/25/2015
 */
/**
 * @name cards
 *		扑克的数值表示： 高四位表示花色， 低四位表示点数;
 *		花色分别是：0x00 方片(DIAMONDS)
 *					0x10 梅花(CLUBS)
 *					0x20 红桃(HEARTS)
 *					0x30 黑桃(SPADES)
 * @{ */
/**  @} */

#include "gamelogic.h"
struct cards;
extern struct cards ghold[];
extern int    gcards[];


#define	DIAMONDS			0x00			/*  方片   */
#define	CLUBS				0x01			/*  梅花   */
#define	HEARTS				0x02			/*  红桃   */
#define	SPADES				0x03			/*  黑桃   */
const char *colordata[] = {
	"DIAMONDS",								/*  方片   */
	"CLUBS",                                /*  梅花   */
	"HEARTS",                               /*  红桃   */
	"SPADES"                                /*  黑桃   */
};
/**
 * @name colornum 
 *		colornum[0]: DIAMONDS
 *		colornum[1]: CLUBS
 *		colornum[2]: HEARTS
 *		colornum[3]: SPADES
 * @{ */
/**  @} */

static int colornum[4];					

/**
 * @name pointnum
 *		pointnum[2~14]: 2~10, J, Q, K, A
 * @{ */
/**  @} */

static int pointnum[15];

const int cardsdata[4][15] = {
	0x00, 0x00, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, /* DIAMONDS */
	0x00, 0x00, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, /* CLUBS	  */
	0x00, 0x00, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, /* HEARTS   */
	0x00, 0x00, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E  /* SPADES   */
};
/**
 * @name suit pattents flag
 * @{ */
/**  @} */

//static int gSTRAIGHT_FLUSH_FLAG  = 0;
static int gFOUR_OF_A_KIND_FLAG  = 0;
static int gFULL_HOUSE_FLAG      = 0;
static int gFLUSH_FLAG			 = 0;
//static int gSTRAIGHT			 = 0;
static int gTHREE_OF_A_KIND_FLAG = 0;
static int gTWO_PAIR_FLAG		 = 0;
static int gONE_PAIR_FLAG		 = 0;
static int gHIGH_CARD_FLAG		 = 0;

int sort(int card[], int m);


int action_msg(int card[], int m)
{
	static int cardsno = 0;
//	int n = cardsno;
	for (int i = 0; i < m; ++i){
		colornum[ (card[i] & LOGIC_MASK_COLOR) >> 8 ] ++;
		pointnum[ card[i] & LOGIC_MASK_POINT ] ++;
		gcards[cardsno ++ ] = card[i];
//		cardsno ++; 
	}
	sort(gcards, cardsno);
	if (cardsno == 7) {
		cardsno = 0;
//		memset(colorno, 0, sizeof(colorno));
//		memset(pointnum, 0, sizeof(pointnum));
	}
	return 0;
}

/**
 * @brief  color_judgement 
 *
 * @param  m
 *
 * @return  
 */
int color_judgement(int m)
{
	if (m < 5) return 0;
	int colormax = 0;
	for (int i = 0; i < 4; ++i) {
		if (colormax < colornum[i]) {
			colormax = colornum[i];
		}
	}
	if (colormax == 5) {
		gFLUSH_FLAG = FLUSH;
		return FLUSH;
	}
	return 0;
}

/**
 * @brief  point_judgement 
 *
 * @return  
 */
int point_judgement(int m) 
{
	for (int i = 2; i < 15; ++i){
		switch (pointnum[i]) {
			case 1:
				gHIGH_CARD_FLAG = HIGH_CARD;
				break;
			case 2:
				if (gTHREE_OF_A_KIND_FLAG) {
					gFULL_HOUSE_FLAG = FULL_HOUSE;
					return FULL_HOUSE;
				} else {
					if (gONE_PAIR_FLAG == ONE_PAIR) {
						gTWO_PAIR_FLAG = TWO_PAIR;
						return TWO_PAIR;
					} else {
						gONE_PAIR_FLAG  = ONE_PAIR;
					}
				}
				break;
//			case TWO_PAIR:
//				gTWO_PAIR_FLAG  = 1;
//				break;
			case 3:
				if (gONE_PAIR_FLAG) {
					gFULL_HOUSE_FLAG = FULL_HOUSE;
					return FULL_HOUSE;
				} else {
					gTHREE_OF_A_KIND_FLAG = THREE_OF_A_KIND;
				}
				break;
//			case FULL_HOUSE:
//				gFULL_HOUSE_FLAG = 1;
//				break;
			case 4:
				gFOUR_OF_A_KIND_FLAG = FOUR_OF_A_KIND;
				return FOUR_OF_A_KIND;
				break;
			default:
				break;
		}
	}
	if (gTHREE_OF_A_KIND_FLAG)
		return THREE_OF_A_KIND;
	else if (gONE_PAIR_FLAG) 
		return ONE_PAIR;
	return HIGH_CARD;
}

/**
 * @brief  straight_judgement 
 *
 * @param  m
 *
 * @return  
 */
int straight_judgement(int m)
{
	if (m < 5) return 0;
	for (int i = 0; i < 5 - 1; ++i) {
		if ((i == 0) && 
			((gcards[i] & LOGIC_MASK_POINT) == 0x0E) && 
			((gcards[i] & LOGIC_MASK_POINT) - (gcards[i+1] & LOGIC_MASK_POINT) == 9)) {
			continue;
		}
		if ((gcards[i] & LOGIC_MASK_POINT) - (gcards[i+1] & LOGIC_MASK_POINT) != 1) {
			return 0;                           /* 不是顺子 */
		}
	}
	if (gFLUSH_FLAG == FLUSH) {
		return STRAIGHT_FLUSH;                               /* 同花顺   */
	}
	return STRAIGHT;                                   /* 顺子     */
}

/**
 * @brief  judgement 
 *
 * @param  m
 *
 * @return  
 */
int judgement(int m)
{
	int f1 = 0, f2 = 0, f3 = 0;
	f1 = straight_judgement(m);
	f2 = point_judgement(m);
	f3 = color_judgement(m);
	return f1 > f2 ? (f1 > f3 ? f1 : f3) :
		(f2 > f3 ? f2 : f3);
}
