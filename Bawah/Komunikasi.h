/*
 * Komunikasi.h
 *
 *  Created on: Mar 2, 2022
 *      Author: Maulana Reyhan Savero
 */
#ifndef KOMUNIKASI_H_
#define KOMUNIKASI_H_

#include "main.h"
#include <stdbool.h>

typedef enum{
	JALA_NOT_FOUND = 0x00U,
	JALAN_PECAH = 0x01U,
	JALAN_KELERENG = 0x02U,
	JALAN_BATU = 0x03U,
	JALAN_NORMAL = 0x04U,
	JALAN_TANGGA = 0x05U
}mode_jalan_t;

typedef struct{
	bool ping;
	bool standby;
	bool jalan;
	bool translasi;
	bool rotasi;
	bool req;
	bool statis;
	bool capit;
	bool serok;
}feedback_t;

typedef enum{
	NO_SKEW = 0x00U,
	MIRING_DEPAN = 0x01U,
	MIRING_BELAKANG = 0x02U,
	MIRING_KANAN = 0x03U,
	MIRING_KIRI = 0x04U
}type_skew_t;

typedef enum{
	PING = 0x01U,
	MOVE_STEADY = 0x02U,
	MOVE_JALAN = 0x03U,
	MOVE_TRANSLASI = 0x04U,
	MOVE_ROTASI = 0x05U,
	SEND_REQ = 0x06U,
	GET_STATIS = 0x07U,
	PLAY_CAPIT = 0x08U,
	PLAY_SEROK = 0x09U
}type_jalan_t;

typedef enum{
	NANJAK_NONE = 0x00U,
	NANJAK_KIRI = 0x01U,
	NANJAK_KANAN = 0x02U
}type_mode_nanjak_t;

typedef enum{
	AMBIL_KORBAN = 0x01U,
	PENYELAMATAN_KORBAN = 0x02U,
	HOME_CAPIT = 0x03U,
	STEADY_CAPIT = 0x04,
	START_CAPIT = 0X05,
	EVAKUASI_CAPIT = 0X06,
}type_capit_t;

typedef enum{
	CAPIT_KORBAN = 0x01U,
	CAPIT_KOSONG = 0x02U,
}type_capit_status_t;

typedef enum{
	CAPIT_NONE = 0x00U,
	CAPIT_FULL = 0x01U,
	CAPIT_HALF = 0x02U,
}type_mode_capit_t;

typedef enum{
	MOVE_DEPAN = 0x01U,
	MOVE_BELAKANG = 0x02U
}type_serok_t;

typedef struct{
	int16_t pos_x;
	int16_t pos_y;
	int16_t pos_z;
	int16_t roll;
	int16_t pitch;
	int16_t yaw;
	int8_t time;
	int8_t walkpoint;
	int8_t mode;
	type_serok_t move;
	type_jalan_t type;
	type_mode_nanjak_t nanjak_mode;
	int8_t speed;
	mode_jalan_t mode_jalan;
	type_capit_t cmd;
	type_capit_status_t status;
	type_mode_capit_t mode_capit;
	int8_t speed_capit;
	type_skew_t skew_mode;
	uint8_t skew_value_xy;
	uint8_t skew_value_z;
}com_get_t;

void komunikasi_init(UART_HandleTypeDef* uart_handler);
bool tx_ping(void);
static uint8_t checksum_generator(uint8_t* arr, uint8_t size);
bool tx_move_steady(void);
bool tx_move_jalan(int16_t pos_x, int16_t pos_y, int16_t pos_z, int8_t speed, mode_jalan_t mode, uint8_t walkpoint, type_mode_nanjak_t nanjak);
bool tx_move_translasi(int8_t value_xy, int8_t value_z, int8_t skew_mode, uint8_t time);
bool tx_move_rotasi(int16_t roll, int16_t pitch, int16_t yaw, int16_t pos_z, int8_t mode, int8_t speed, uint8_t langkah);
void rx_start(void);
void rx_feedback(feedback_t* fed);
void rx_start_get(void);
void rx_get(com_get_t* get);
bool tx_statis(int16_t pos_x, int16_t pos_y, int16_t pos_z);
bool tx_capit(type_capit_t cmd, type_capit_status_t status, int8_t speed_capit, type_mode_capit_t mode);
bool tx_serok(type_serok_t cmd);
#endif