#ifndef FAF_REGISTRY_TESTS_H
#define FAF_REGISTRY_TESTS_H

void FAF_Registry_Init_Valid_T(void);
void FAF_Registry_Init_Out_Bounds_T(void);
void FAF_Registry_Init_Poison_T(void);
void FAF_Registry_Init_Type_Mismatch_T(void);

void FAF_Registry_Dispose_Valid_T(void);
void FAF_Registry_Dispose_Out_Bounds_T(void);
void FAF_Registry_Dispose_Poison_T(void);
void FAF_Registry_Dispose_Type_Mismatch_T(void);

#endif // FAF_REGISTRY_TESTS_H