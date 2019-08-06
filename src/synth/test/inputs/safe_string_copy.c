#include "string_lib.h"

HRESULT safe_string_copy(char* pszDest, int cchDest, char* pszSrc)
{
  HRESULT hr = S_OK;

  if (!pszDest) {
    // can not null terminate a zero-byte pszDest buffer
    hr = STRSAFE_E_INVALID_PARAMETER;
  } else {
    while (cchDest && (*pszSrc != '\0')) {
      *pszDest++ = *pszSrc++;
      cchDest--;
    }

    if (cchDest == 0) {
      // we are going to truncate pszDest
      pszDest--;
      hr = STRSAFE_E_INSUFFICIENT_BUFFER;
    }

    *pszDest = '\0';
  }

  return hr;
}
