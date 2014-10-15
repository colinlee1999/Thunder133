VOID GetBitmapWidthAndHeight(char *address,LONG *width,LONG *height)
{
	FILE *fp ;
	fp = fopen(address,"r") ;
	fseek(fp,18L,0) ;
	fread(width,sizeof(LONG),1,fp); 
	fseek(fp,22L,0) ;
	fread(height,sizeof(LONG),1,fp); 
	fclose(fp) ;
}
