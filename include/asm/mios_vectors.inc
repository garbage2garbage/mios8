; $Id$

MIOS_MIDI_BeginStream                   EQU	0x2c00
MIOS_MIDI_DeviceIDAutoSet               EQU	0x2c04
MIOS_MIDI_DeviceIDGet                   EQU	0x2c08
MIOS_MIDI_DeviceIDSet                   EQU	0x2c0c
MIOS_MIDI_EndStream                     EQU	0x2c10
MIOS_MIDI_Init                          EQU	0x2c14
MIOS_MIDI_InterfaceAutoSet              EQU	0x2c18
MIOS_MIDI_InterfaceGet                  EQU	0x2c1c
MIOS_MIDI_InterfaceSet                  EQU	0x2c20
MIOS_MIDI_MergerGet                     EQU	0x2c24
MIOS_MIDI_MergerSet                     EQU	0x2c28
MIOS_MIDI_RxBufferFree                  EQU	0x2c2c
MIOS_MIDI_RxBufferGet                   EQU	0x2c30
MIOS_MIDI_RxBufferPut                   EQU	0x2c34
MIOS_MIDI_RxBufferUsed                  EQU	0x2c38
MIOS_MIDI_TxBufferFlush                 EQU	0x2c3c
MIOS_MIDI_TxBufferFree                  EQU	0x2c40
MIOS_MIDI_TxBufferGet                   EQU	0x2c44
MIOS_MIDI_TxBufferPut                   EQU	0x2c48
MIOS_MIDI_TxBufferUsed                  EQU	0x2c4c
MIOS_MPROC_MergerDisable                EQU	0x2c50
MIOS_MPROC_MergerEnable                 EQU	0x2c54
MIOS_MPROC_MergerGet                    EQU	0x2c58
MIOS_AIN_DeadbandGet                    EQU	0x2c5c
MIOS_AIN_DeadbandSet                    EQU	0x2c60
MIOS_AIN_Muxed                          EQU	0x2c64
MIOS_AIN_NumberGet                      EQU	0x2c68
MIOS_AIN_NumberSet                      EQU	0x2c6c
MIOS_AIN_Pin7bitGet                     EQU	0x2c70
MIOS_AIN_PinGet                         EQU	0x2c74
MIOS_AIN_PinLSBGet                      EQU	0x2c78
MIOS_AIN_PinMSBGet                      EQU	0x2c7c
MIOS_AIN_UnMuxed                        EQU	0x2c80
MIOS_MF_PWM_DutyCycleDownGet            EQU	0x2c84
MIOS_MF_PWM_DutyCycleDownSet            EQU	0x2c88
MIOS_MF_PWM_DutyCycleUpGet              EQU	0x2c8c
MIOS_MF_PWM_DutyCycleUpSet              EQU	0x2c90
MIOS_MF_DeadbandGet                     EQU	0x2c94
MIOS_MF_DeadbandSet                     EQU	0x2c98
MIOS_MF_Disable                         EQU	0x2c9c
MIOS_MF_Enable                          EQU	0x2ca0
MIOS_MF_FaderMove                       EQU	0x2ca4
MIOS_MF_SuspendDisable                  EQU	0x2ca8
MIOS_MF_SuspendEnable                   EQU	0x2cac
MIOS_MF_SuspendGet                      EQU	0x2cb0
MIOS_DIN_PinGet                         EQU	0x2cb4
MIOS_DIN_SRGet                          EQU	0x2cb8
MIOS_DOUT_PinGet                        EQU	0x2cbc
MIOS_DOUT_PinSet                        EQU	0x2cc0
MIOS_DOUT_PinSet0                       EQU	0x2cc4
MIOS_DOUT_PinSet1                       EQU	0x2cc8
MIOS_DOUT_SRGet                         EQU	0x2ccc
MIOS_DOUT_SRSet                         EQU	0x2cd0
MIOS_ENC_Abs7bitAdd                     EQU	0x2cd4
MIOS_ENC_Abs7bitGet                     EQU	0x2cd8
MIOS_ENC_Abs7bitSet                     EQU	0x2cdc
MIOS_ENC_NumberGet                      EQU	0x2ce0
MIOS_ENC_SpeedGet                       EQU	0x2ce4
MIOS_ENC_SpeedSet                       EQU	0x2ce8
MIOS_SRIO_NumberGet                     EQU	0x2cec
MIOS_SRIO_NumberSet                     EQU	0x2cf0
MIOS_SRIO_TS_SensitivityGet             EQU	0x2cf4
MIOS_SRIO_TS_SensitivitySet             EQU	0x2cf8
MIOS_SRIO_UpdateFrqGet                  EQU	0x2cfc
MIOS_SRIO_UpdateFrqSet                  EQU	0x2d00
MIOS_LCD_Clear                          EQU	0x2d04
MIOS_LCD_Cmd                            EQU	0x2d08
MIOS_LCD_CursorGet                      EQU	0x2d0c
MIOS_LCD_CursorSet                      EQU	0x2d10
MIOS_LCD_Data                           EQU	0x2d14
MIOS_LCD_Init                           EQU	0x2d18
MIOS_LCD_PrintBCD1	                EQU	0x2d1c
MIOS_LCD_PrintBCD2                      EQU	0x2d20
MIOS_LCD_PrintBCD3                      EQU	0x2d24
MIOS_LCD_PrintChar	                EQU	0x2d28
MIOS_LCD_PrintHex1	                EQU	0x2d2c
MIOS_LCD_PrintHex2                      EQU	0x2d30
MIOS_LCD_PrintMessage                   EQU	0x2d34
MIOS_LCD_PrintPreconfString             EQU	0x2d38
MIOS_LCD_PrintString                    EQU	0x2d3c
MIOS_LCD_TypeAutoSet                    EQU	0x2d40
MIOS_LCD_TypeGet                        EQU	0x2d44
MIOS_LCD_TypeSet                        EQU	0x2d48
MIOS_LCD_YAddressGet                    EQU	0x2d4c
MIOS_LCD_YAddressSet                    EQU	0x2d50
MIOS_GLCD_FontInit                      EQU	0x2d54
MIOS_GLCD_GCursorGet                    EQU	0x2d58
MIOS_GLCD_GCursorSet                    EQU	0x2d5c
MIOS_EEPROM_Read                        EQU	0x2d60
MIOS_EEPROM_Write                       EQU	0x2d64
MIOS_FLASH_Read                         EQU	0x2d68
MIOS_FLASH_Write                        EQU	0x2d6c
MIOS_BANKSTICK_Read                     EQU	0x2d70
MIOS_BANKSTICK_Write                    EQU	0x2d74
MIOS_TIMER_Init                         EQU	0x2d78
MIOS_TIMER_Start                        EQU	0x2d7c
MIOS_TIMER_Stop                         EQU	0x2d80
MIOS_HLP_AddressFromTable               EQU	0x2d84
MIOS_HLP_GetBitANDMask                  EQU	0x2d88
MIOS_HLP_GetBitORMask                   EQU	0x2d8c
MIOS_HLP_GetIndex_2bytes                EQU	0x2d90
MIOS_HLP_GetIndex_4bytes                EQU	0x2d94
MIOS_HLP_IndirectJump                   EQU	0x2d98
MIOS_Delay                              EQU	0x2d9c
MIOS_GPCounterGet                       EQU	0x2da0
MIOS_Reset                              EQU	0x2da4
MIOS_SystemResume                       EQU	0x2da8
MIOS_SystemSuspend                      EQU	0x2dac
MIOS_UserResume                         EQU	0x2db0
MIOS_UserSuspend                        EQU	0x2db4
MIOS_HLP_16bitAddSaturate		EQU	0x2db8
MIOS_DIN_PinAutoRepeatEnable		EQU	0x2dbc
MIOS_DIN_PinAutoRepeatDisable		EQU	0x2dc0
MIOS_DIN_PinAutoRepeatGet		EQU	0x2dc4
MIOS_CLCD_SpecialCharInit		EQU	0x2dc8
MIOS_CLCD_SpecialCharsInit		EQU	0x2dcc
MIOS_AIN_DynamicPrioSet			EQU	0x2dd0
MIOS_AIN_DynamicPrioGet			EQU	0x2dd4
MIOS_AIN_LastPinsGet			EQU	0x2dd8
MIOS_BANKSTICK_CtrlSet			EQU	0x2ddc
MIOS_BANKSTICK_CtrlGet			EQU	0x2de0
MIOS_BANKSTICK_WritePage		EQU	0x2de4
MIOS_HLP_Dec2BCD			EQU	0x2de8
MIOS_LCD_PrintBCD4			EQU	0x2dec
MIOS_LCD_PrintBCD5                      EQU	0x2df0
MIOS_LCD_MessageStart			EQU	0x2df4
MIOS_LCD_MessageStop			EQU	0x2df8
MIOS_MF_PWM_PeriodGet                   EQU	0x2dfc
MIOS_MF_PWM_PeriodSet                   EQU	0x2e00
MIOS_IIC_Start				EQU	0x2e04
MIOS_IIC_Stop				EQU	0x2e08
MIOS_IIC_ByteSend			EQU	0x2e0c
MIOS_IIC_ByteReceive			EQU	0x2e10
MIOS_IIC_AckSend			EQU	0x2e14
MIOS_IIC_NakSend			EQU	0x2e18
MIOS_IIC_CtrlSet			EQU	0x2e1c
MIOS_IIC_CtrlGet			EQU	0x2e20
MIOS_SRIO_DebounceSet			EQU	0x2e24
MIOS_SRIO_DebounceGet			EQU	0x2e28
MIOS_MF_TouchDetectionReset		EQU	0x2e2c
MIOS_BANKSTICK_ReadPage			EQU	0x2e30
MIOS_EEPROM_ReadPage			EQU	0x2e34
MIOS_EEPROM_WritePage			EQU	0x2e38
MIOS_TIMER_ReInit			EQU	0x2e3c
MIOS_RESERVED_144                       EQU	0x2e40
MIOS_RESERVED_145                       EQU	0x2e44
MIOS_RESERVED_146                       EQU	0x2e48
MIOS_RESERVED_147                       EQU	0x2e4c
MIOS_RESERVED_148                       EQU	0x2e50
MIOS_RESERVED_149                       EQU	0x2e54
MIOS_RESERVED_150                       EQU	0x2e58
MIOS_RESERVED_151                       EQU	0x2e5c
MIOS_RESERVED_152                       EQU	0x2e60
MIOS_RESERVED_153                       EQU	0x2e64
MIOS_RESERVED_154                       EQU	0x2e68
MIOS_RESERVED_155                       EQU	0x2e6c
MIOS_RESERVED_156                       EQU	0x2e70
MIOS_RESERVED_157                       EQU	0x2e74
MIOS_RESERVED_158                       EQU	0x2e78
MIOS_RESERVED_159                       EQU	0x2e7c
MIOS_RESERVED_160                       EQU	0x2e80
MIOS_RESERVED_161                       EQU	0x2e84
MIOS_RESERVED_162                       EQU	0x2e88
MIOS_RESERVED_163                       EQU	0x2e8c
MIOS_RESERVED_164                       EQU	0x2e90
MIOS_RESERVED_165                       EQU	0x2e94
MIOS_RESERVED_166                       EQU	0x2e98
MIOS_RESERVED_167                       EQU	0x2e9c
MIOS_RESERVED_168                       EQU	0x2ea0
MIOS_RESERVED_169                       EQU	0x2ea4
MIOS_RESERVED_170                       EQU	0x2ea8
MIOS_RESERVED_171                       EQU	0x2eac
MIOS_RESERVED_172                       EQU	0x2eb0
MIOS_RESERVED_173                       EQU	0x2eb4
MIOS_RESERVED_174                       EQU	0x2eb8
MIOS_RESERVED_175                       EQU	0x2ebc
MIOS_RESERVED_176                       EQU	0x2ec0
MIOS_RESERVED_177                       EQU	0x2ec4
MIOS_RESERVED_178                       EQU	0x2ec8
MIOS_RESERVED_179                       EQU	0x2ecc
MIOS_RESERVED_180                       EQU	0x2ed0
MIOS_RESERVED_181                       EQU	0x2ed4
MIOS_RESERVED_182                       EQU	0x2ed8
MIOS_RESERVED_183                       EQU	0x2edc
MIOS_RESERVED_184                       EQU	0x2ee0
MIOS_RESERVED_185                       EQU	0x2ee4
MIOS_RESERVED_186                       EQU	0x2ee8
MIOS_RESERVED_187                       EQU	0x2eec
MIOS_RESERVED_188                       EQU	0x2ef0
MIOS_RESERVED_189                       EQU	0x2ef4
MIOS_RESERVED_190                       EQU	0x2ef8
MIOS_RESERVED_191                       EQU	0x2efc
MIOS_RESERVED_192                       EQU	0x2f00
MIOS_RESERVED_193                       EQU	0x2f04
MIOS_RESERVED_194                       EQU	0x2f08
MIOS_RESERVED_195                       EQU	0x2f0c
MIOS_RESERVED_196                       EQU	0x2f10
MIOS_RESERVED_197                       EQU	0x2f14
MIOS_RESERVED_198                       EQU	0x2f18
MIOS_RESERVED_199                       EQU	0x2f1c
MIOS_RESERVED_200                       EQU	0x2f20
MIOS_RESERVED_201                       EQU	0x2f24
MIOS_RESERVED_202                       EQU	0x2f28
MIOS_RESERVED_203                       EQU	0x2f2c
MIOS_RESERVED_204                       EQU	0x2f30
MIOS_RESERVED_205                       EQU	0x2f34
MIOS_RESERVED_206                       EQU	0x2f38
MIOS_RESERVED_207                       EQU	0x2f3c
MIOS_RESERVED_208                       EQU	0x2f40
MIOS_RESERVED_209                       EQU	0x2f44
MIOS_RESERVED_210                       EQU	0x2f48
MIOS_RESERVED_211                       EQU	0x2f4c
MIOS_RESERVED_212                       EQU	0x2f50
MIOS_RESERVED_213                       EQU	0x2f54
MIOS_RESERVED_214                       EQU	0x2f58
MIOS_RESERVED_215                       EQU	0x2f5c
MIOS_RESERVED_216                       EQU	0x2f60
MIOS_RESERVED_217                       EQU	0x2f64
MIOS_RESERVED_218                       EQU	0x2f68
MIOS_RESERVED_219                       EQU	0x2f6c
MIOS_RESERVED_220                       EQU	0x2f70
MIOS_RESERVED_221                       EQU	0x2f74
MIOS_RESERVED_222                       EQU	0x2f78
MIOS_RESERVED_223                       EQU	0x2f7c
MIOS_RESERVED_224                       EQU	0x2f80
MIOS_RESERVED_225                       EQU	0x2f84
MIOS_RESERVED_226                       EQU	0x2f88
MIOS_RESERVED_227                       EQU	0x2f8c
MIOS_RESERVED_228                       EQU	0x2f90
MIOS_RESERVED_229                       EQU	0x2f94
MIOS_RESERVED_230                       EQU	0x2f98
MIOS_RESERVED_231                       EQU	0x2f9c
MIOS_RESERVED_232                       EQU	0x2fa0
MIOS_RESERVED_233                       EQU	0x2fa4
MIOS_RESERVED_234                       EQU	0x2fa8
MIOS_RESERVED_235                       EQU	0x2fac
MIOS_RESERVED_236                       EQU	0x2fb0
MIOS_RESERVED_237                       EQU	0x2fb4
MIOS_RESERVED_238                       EQU	0x2fb8
MIOS_RESERVED_239                       EQU	0x2fbc
MIOS_RESERVED_240                       EQU	0x2fc0
MIOS_RESERVED_241                       EQU	0x2fc4
MIOS_RESERVED_242                       EQU	0x2fc8
MIOS_RESERVED_243                       EQU	0x2fcc
MIOS_RESERVED_244                       EQU	0x2fd0
MIOS_RESERVED_245                       EQU	0x2fd4
MIOS_RESERVED_246                       EQU	0x2fd8
MIOS_RESERVED_247                       EQU	0x2fdc
MIOS_RESERVED_248                       EQU	0x2fe0
MIOS_RESERVED_249                       EQU	0x2fe4
MIOS_RESERVED_250                       EQU	0x2fe8
MIOS_RESERVED_251                       EQU	0x2fec
MIOS_RESERVED_252                       EQU	0x2ff0
MIOS_RESERVED_253                       EQU	0x2ff4
MIOS_RESERVED_254                       EQU	0x2ff8
MIOS_RESERVED_255                       EQU	0x2ffc
