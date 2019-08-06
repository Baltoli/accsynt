#pragma once

#define HRESULT int

#define S_OK ((HRESULT)0x00000000L)

#define STRSAFE_E_INSUFFICIENT_BUFFER                                          \
  ((HRESULT)0x8007007AL) // 0x7A = 122L = ERROR_INSUFFICIENT_BUFFER

#define STRSAFE_E_INVALID_PARAMETER                                            \
  ((HRESULT)0x80070057L) // 0x57 =  87L = ERROR_INVALID_PARAMETER
