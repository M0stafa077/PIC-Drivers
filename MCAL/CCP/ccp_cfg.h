/* 
 * File:   ccp_cfg.h
 * Author: Mostafa Asaad
 *
 * Created on February 12, 2024, 5:29 PM
 */

#ifndef CCP_CFG_H
#define	CCP_CFG_H

/* --------------- Section: Macro Declarations --------------- */
#define CCP_CFG_CAPTURE_MODE_SELECTED       (0X00)
#define CCP_CFG_COMPARE_MODE_SELECTED       (0X01)
#define CCP_CFG_PWM_MODE_SELECTED           (0X02)

#define CCP1_CFG_SELECTED_MODE              CCP_CFG_COMPARE_MODE_SELECTED
#define CCP2_CFG_SELECTED_MODE              CCP_CFG_PWM_MODE_SELECTED

#endif	/* CCP_CFG_H */

