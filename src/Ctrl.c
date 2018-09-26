/******************************************************************************/
/* src/Ctrl.c                                                                 */
/*                                                                 2018/09/26 */
/* Copyright (C) 2018 Mochi.                                                  */
/******************************************************************************/
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* 共通ヘッダ */
#include <mterm.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <kernel/library.h>

/* モジュールヘッダ */
#include "i8042.h"


/******************************************************************************/
/* グローバル関数定義                                                         */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief       出力バッファ読込
 * @details     キーボードコントローラの出力バッファを1byte読み込む。
 * 
 * @param[in]   *pData 格納先
 * 
 * @return      読込結果を返す。
 * @retval      true  正常に読込完了
 * @retval      false 出力バッファが空
 */
/******************************************************************************/
bool CtrlReadOutput( uint8_t *pData )
{
    uint8_t  status;    /* ステータス */
    uint32_t ret;       /* 戻り値     */
    
    /* 初期化 */
    ret = MK_IOPORT_RET_SUCCESS;
    
    /* ステータス読込 */
    ret = MkIoPortInByte( I8042_PORT_STATUS,    /* I/Oポート番号 */
                          &status,              /* 格納先        */
                          1,                    /* 読込回数      */
                          NULL               ); /* エラー番号    */
    
    /* 読込結果判定 */
    if ( ret != MK_IOPORT_RET_SUCCESS ) {
        /* 失敗 */
        
        /* [TODO]アボート */
        *( ( uint32_t * ) NULL ) = 0xDEADDEAD;
    }
    
    /* OBFチェック */
    if ( ( status & I8042_STATUS_OBF ) == false ) {
        /* 出力バッファが空 */
        
        return false;
    }
    
    /* 出力バッファ読込 */
    ret = MkIoPortInByte( I8042_PORT_OUTPUT,    /* I/Oポート番号 */
                          pData,                /* 格納先        */
                          1,                    /* 読込回数      */
                          NULL               ); /* エラー番号    */
    
    /* 読込結果判定 */
    if ( ret != MK_IOPORT_RET_SUCCESS ) {
        /* 失敗 */
        
        /* [TODO]アボート */
        *( ( uint32_t * ) NULL ) = 0xDEADDEAD;
    }
    
    return true;
}



/******************************************************************************/
/**
 * @brief       入力バッファ書込み
 * @details     キーボードコントローラの入力バッファに1byte書き込む。
 * 
 * @param[in]   *pData 書込みデータ
 * 
 * @return      読込結果を返す。
 * @retval      true  正常に書込み完了
 * @retval      false 入力バッファがフル
 */
/******************************************************************************/
bool CtrlWriteInput( uint8_t *pData )
{
    uint8_t  status;    /* ステータス */
    uint32_t ret;       /* 戻り値     */
    
    /* 初期化 */
    ret = MK_IOPORT_RET_SUCCESS;
    
    /* ステータス読込 */
    ret = MkIoPortInByte( I8042_PORT_STATUS,    /* I/Oポート番号 */
                          &status,              /* 格納先        */
                          1,                    /* 読込回数      */
                          NULL               ); /* エラー番号    */
    
    /* 読込結果判定 */
    if ( ret != MK_IOPORT_RET_SUCCESS ) {
        /* 失敗 */
        
        /* [TODO]アボート */
        *( ( uint32_t * ) NULL ) = 0xDEADDEAD;
    }
    
    /* IBFチェック */
    if ( ( status & I8042_STATUS_IBF ) != false ) {
        /* 入力バッファがフル */
        
        return false;
    }
    
    /* 入力バッファ書込 */
    ret = MkIoPortOutByte( I8042_PORT_INPUT,    /* I/Oポート番号 */
                           pData,               /* 格納先        */
                           1,                   /* 書込回数      */
                           NULL               );/* エラー番号    */
    
    /* 書込結果判定 */
    if ( ret != MK_IOPORT_RET_SUCCESS ) {
        /* 失敗 */
        
        /* [TODO]アボート */
        *( ( uint32_t * ) NULL ) = 0xDEADDEAD;
    }
    
    return true;
}


/******************************************************************************/
