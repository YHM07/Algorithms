/**
 * @file gamelogic.h
 * @brief 
 * @author H.M.Yang, hmyang07@gmail.com
 * @version v1.0
 * @date 05/25/2015
 */

#ifndef _GAMELOGIC_H
#define _GAMELOGIC_H

#define	LOGIC_MASK_COLOR	0xF0			/* color   */
#define	LOGIC_MASK_POINT	0x0F			/* point   */

#ifndef SUIT_PATTENTS 
#define SUIT_PATTENTS

#define	HIGH_CARD			0x01			/*	高牌   */
#define	ONE_PAIR			0x02			/*  一对   */
#define	TWO_PAIR			0x03			/*  两对   */
#define	THREE_OF_A_KIND		0x04			/*  三条   */
#define	STRAIGHT			0x05			/*  顺子   */
#define	FLUSH				0x06			/*  同花   */
#define	FULL_HOUSE			0x07			/*  葫芦   */
#define	FOUR_OF_A_KIND		0x08 			/*  四条   */
#define	STRAIGHT_FLUSH		0x09			/*  同花顺 */

#endif 

#define	DIAMONDS			0x00			/*  方片   */
#define	CLUBS				0x01			/*  梅花   */
#define	HEARTS				0x02			/*  红桃   */
#define	SPADES				0x03			/*  黑桃   */


int action_msg(int card[], int m);
int sort(int card[], int m);

#endif                                          /* _GAMELOGIC_H */
