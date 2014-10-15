BOOL TransparentBltU(
HDC dcDest,         // handle to Dest DC
int nXOriginDest,   // x-coord of destination upper-left corner
int nYOriginDest,   // y-coord of destination upper-left corner
int nWidthDest,     // width of destination rectangle
int nHeightDest,    // height of destination rectangle
HDC dcSrc,          // handle to source DC
int nXOriginSrc,    // x-coord of source upper-left corner
int nYOriginSrc,    // y-coord of source upper-left corner
int nWidthSrc,      // width of source rectangle
int nHeightSrc,     // height of source rectangle
UINT crTransparent  // color to make transparent
)
{
if (nWidthDest < 1) return 0;
if (nWidthSrc < 1) return 0;
if (nHeightDest < 1) return 0;
if (nHeightSrc < 1) return 0;
 
HDC dc = CreateCompatibleDC(NULL);
HBITMAP bitmap = CreateBitmap(nWidthSrc, nHeightSrc, 1, GetDeviceCaps(dc,
BITSPIXEL), NULL);
 
if (bitmap == NULL)
{
DeleteDC(dc);   
return 0;
}
 
HBITMAP oldBitmap = (HBITMAP)SelectObject(dc, bitmap);
 
if (!BitBlt(dc, 0, 0, nWidthSrc, nHeightSrc, dcSrc, nXOriginSrc,
nYOriginSrc, SRCCOPY))
{
SelectObject(dc, oldBitmap);
DeleteObject(bitmap);       
DeleteDC(dc);               
return 0;
}
 
HDC maskDC = CreateCompatibleDC(NULL);
HBITMAP maskBitmap = CreateBitmap(nWidthSrc, nHeightSrc, 1, 1, NULL);
 
if (maskBitmap == NULL)
{
SelectObject(dc, oldBitmap);
DeleteObject(bitmap);       
DeleteDC(dc);               
DeleteDC(maskDC);           
return 0;
}
 
HBITMAP oldMask =  (HBITMAP)SelectObject(maskDC, maskBitmap);
 
SetBkColor(maskDC, RGB(0,0,0));
SetTextColor(maskDC, RGB(255,255,255));
if (!BitBlt(maskDC, 0,0,nWidthSrc,nHeightSrc,NULL,0,0,BLACKNESS))
{
SelectObject(maskDC, oldMask);
DeleteObject(maskBitmap);     
DeleteDC(maskDC);             
SelectObject(dc, oldBitmap);  
DeleteObject(bitmap);         
DeleteDC(dc);                 
return 0;
}
 
SetBkColor(dc, crTransparent);
BitBlt(maskDC, 0,0,nWidthSrc,nHeightSrc,dc,0,0,SRCINVERT);
 
SetBkColor(dc, RGB(0,0,0));
SetTextColor(dc, RGB(255,255,255));
BitBlt(dc, 0,0,nWidthSrc,nHeightSrc,maskDC,0,0,SRCAND);
 
HDC newMaskDC = CreateCompatibleDC(NULL);
HBITMAP newMask;
newMask = CreateBitmap(nWidthDest, nHeightDest, 1,
GetDeviceCaps(newMaskDC, BITSPIXEL), NULL);
 
if (newMask == NULL)
{
SelectObject(dc, oldBitmap);
DeleteDC(dc);
SelectObject(maskDC, oldMask);
DeleteDC(maskDC);
DeleteDC(newMaskDC);
DeleteObject(bitmap);    
DeleteObject(maskBitmap);
return 0;
}
 
SetStretchBltMode(newMaskDC, COLORONCOLOR);
HBITMAP oldNewMask = (HBITMAP) SelectObject(newMaskDC, newMask);
StretchBlt(newMaskDC, 0, 0, nWidthDest, nHeightDest, maskDC, 0, 0,
nWidthSrc, nHeightSrc, SRCCOPY);
 
SelectObject(maskDC, oldMask);
DeleteDC(maskDC);
DeleteObject(maskBitmap);
 
HDC newImageDC = CreateCompatibleDC(NULL);
HBITMAP newImage = CreateBitmap(nWidthDest, nHeightDest, 1,
GetDeviceCaps(newMaskDC, BITSPIXEL), NULL);
 
if (newImage == NULL)
{
SelectObject(dc, oldBitmap);
DeleteDC(dc);
DeleteDC(newMaskDC);
DeleteObject(bitmap);    
return 0;
}
 
HBITMAP oldNewImage = (HBITMAP)SelectObject(newImageDC, newImage);
StretchBlt(newImageDC, 0, 0, nWidthDest, nHeightDest, dc, 0, 0, nWidthSrc,
nHeightSrc, SRCCOPY);
 
SelectObject(dc, oldBitmap);
DeleteDC(dc);
DeleteObject(bitmap);    
 
BitBlt( dcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest,
newMaskDC, 0, 0, SRCAND);
 
BitBlt( dcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest,
newImageDC, 0, 0, SRCPAINT);
 
SelectObject(newImageDC, oldNewImage);
DeleteDC(newImageDC);
SelectObject(newMaskDC, oldNewMask);
DeleteDC(newMaskDC);
DeleteObject(newImage);  
DeleteObject(newMask);   
 
return 1;
}
