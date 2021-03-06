// https://github.com/NyaMisty/mkxqimage_rev/blob/master/mkxqimage.c

//----- (00000000004036EC) ----------------------------------------------------
int64_t get_ssh_key()
{
  char magic[100]; // [xsp+EA8h] [xbp+18h] BYREF
  char snStr[100]; // [xsp+F10h] [xbp+80h] BYREF
  char Sn[100]; // [xsp+F78h] [xbp+E8h] BYREF
  unsigned char md5Output[16]; // [xsp+FE0h] [xbp+150h] BYREF
  FILE *stream; // [xsp+FF0h] [xbp+160h]
  int i; // [xsp+FFCh] [xbp+16Ch]

  memset(md5Output, 0, 16);
  memset(Sn, 0, 100);
  memset(snStr, 0, 100);
  memset(magic, 0, 100);
#ifdef ONDEVICE
  stream = popen("nvram get SN", "r");
#else
  stream = fopen("SN.txt", "r");
#endif
  if ( !stream )
    return puts("Failed to run command");

  while ( fgets(Sn, 100, stream) )
    sscanf(Sn, "%s", snStr);

#ifdef ONDEVICE
  pclose(stream);
#else
  fclose(stream);
#endif
  transpostGuid("d44fb0960aa0-a5e6-4a30-250f-6d2df50a", magic);
  sprintf(Sn, "%s%s", snStr, magic);
  calcMd5(md5Output, Sn);
  memset(Sn, 0, sizeof(Sn));
  for ( i = 0; i <= 3; ++i )
    printf("%x%x", (md5Output[i] >> 4) & 0xF, md5Output[i] & 0xF);
  return puts(Sn);
}

//----- (000000000040355C) ----------------------------------------------------
int64_t transpostGuid(uint8_t *a1, char *outbuf)
{
    char *v2;         // x0
    int64_t result;   // x0
    char mat[8][32];  // [xsp+28h] [xbp+28h] BYREF
    size_t n;         // [xsp+12Ch] [xbp+12Ch]
    char *curRow;     // [xsp+130h] [xbp+130h]
    int rowI;         // [xsp+138h] [xbp+138h]
    unsigned int row; // [xsp+13Ch] [xbp+13Ch]

    row = 0;
    rowI = 0;
    n = 0;
    memset(mat, 0, sizeof(mat));
    while (*a1)
    {
        if (*a1 == '-')
        {
            mat[row++][rowI] = 0;
            rowI = 0;
        }
        else
        {
            mat[row][rowI++] = *a1;
        }
        ++a1;
    }
    mat[row][rowI] = 0;
    curRow = outbuf;
    while (1)
    {
        result = row;
        if ((row & 0x80000000) != 0)
            break;
        n = strlen(mat[row]);
        strncpy(curRow, mat[row], n);
        curRow += (int)n;
        if (row)
        {
            v2 = curRow++;
            *v2 = '-';
        }
        else
        {
            *curRow = 0;
        }
        --row;
    }
    return result;
}
