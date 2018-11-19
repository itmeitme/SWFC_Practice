extern Data query(int supose[]);
 
bool arr[10000] = { 0 };
 
bool is_possible(int suppose[]) {
 
   int supposeCheck[10] = { 0 };
 
   for (int idx = 0; idx < 4; ++idx) {
 
      if (suppose[idx] < 0 || suppose[idx] >= 10 || supposeCheck[suppose[idx]] > 0) return false;
 
      supposeCheck[suppose[idx]]++;
 
   }
 
   return true;
 
}
 
bool chk_match(int suppose[4], int comp[4], Data result) {
 
   bool numsCheck[10] = { 0 };
   for (int idx = 0; idx < 4; ++idx) {
      numsCheck[comp[idx]] = 1;
   }
   //printf("suppose : %d%d%d%d\n",suppose[0], suppose[1], suppose[2], suppose[3]);
   //printf("comp    : %d%d%d%d\n", comp[0], comp[1], comp[2], comp[3]);
 
   Data comp_Data = { 0 };
 
   for (int idx = 0; idx < 4; ++idx) {
 
      if (suppose[idx] == comp[idx])
      {
         comp_Data.strike++;
      }
      else if (numsCheck[suppose[idx]])
      {
         comp_Data.ball++;
      }
 
   }
   if ((comp_Data.strike == result.strike) && (comp_Data.ball == result.ball)) {
      return 1;
   }
   else {
      return 0;
   }
 
}
 
void digits_to_arr(int a, int d[4]) {
   d[3] = a % 10;
   a /= 10;
   d[2] = a % 10;
   a /= 10;
   d[1] = a % 10;
   a /= 10;
   d[0] = a % 10;
   a /= 10;
 
}
 
void tryBest(int suppose[]) {
 
   for (int i = 0; i < 10000; i++) {
      digits_to_arr(i, suppose);
      arr[i] = is_possible(suppose);
   }
   int comp_digits[4][4] = { {0,1,2,3}, {4,5,6,7}, {8,9,0,1}, {2,3,4,5} };
 
   Data result_Data;
   int d[4] = { 0 };
   int d2[4] = { 0 };
   /*
   printf("strike : %d\n", result_Data.strike);
   printf("ball : %d\n", result_Data.ball);
   printf("chk : %d\n", chk_match(comp_digits[0],d, result_Data));
   */
 
   for (int comp_cnt = 0; comp_cnt < 4; comp_cnt++) {
      result_Data = query(comp_digits[comp_cnt]);
      for (int i = 0; i < 10000; i++) {
         if (arr[i]) {
            digits_to_arr(i, d);
            arr[i] = chk_match(comp_digits[comp_cnt], d, result_Data);
         }
         /*
         if (arr[i]) {
            printf("%d\n", i);
         }
         */
      }
      //printf("-------------------------------------\n");
   }
   int write_index1 = 0;
   int write_index2 = 0;
   int candidate[1000] = { 0 };
 
   for (int i = 0; i < 10000; i++) {
      if (arr[i]) {
         candidate[write_index1++] = i;
      }
   }
   while (write_index1 > 1) {
      digits_to_arr(candidate[0], d);
      result_Data = query(d);
      if (result_Data.strike == 4) {
         suppose[0] = d[0];
         suppose[1] = d[1];
         suppose[2] = d[2];
         suppose[3] = d[3];
      }
      for (int i = 1; i < write_index1; i++) {
         digits_to_arr(candidate[i], d2);
         arr[candidate[i]] = chk_match(d, d2, result_Data);
      }
      for (int i = 1; i < write_index1; i++) {
         if (arr[candidate[i]]) {
            //printf("%d\n", candidate[i]);
            candidate[write_index2++] = candidate[i];
         }
      }
      write_index1 = write_index2;
      write_index2 = 0;
   }
   digits_to_arr(candidate[0], d);
   suppose[0] = d[0];
   suppose[1] = d[1];
   suppose[2] = d[2];
   suppose[3] = d[3];
 
}
