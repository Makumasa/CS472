#include <stdio.h>
#include <string.h>

typedef enum { false, true } bool;

unsigned int eax;
unsigned int ebx;
unsigned int ecx;
unsigned int edx;

unsigned int* registers[4] = { &eax, &ebx, &ecx, &edx };

enum CACHE_INFO_TYPE {
    NONE,
    TLB,
    CACHE,
    MISSING,
    PREFETCH,
    NOREPORT
};

/* Source: https://github.com/tianocore/edk2/blob/master/UefiCpuPkg/Application/Cpuid/Cpuid.c */
typedef struct {
    unsigned char   CacheDescriptor;
    int             Type;
    char*           Description;
} cpuid_cache_info;

/* Source: https://github.com/tianocore/edk2/blob/master/UefiCpuPkg/Application/Cpuid/Cpuid.c */
cpuid_cache_info  cpuid_cache_info_table[] = {
    { 0x00, NONE,       "Null descriptor, this byte contains no information\n" },
    { 0x01, TLB,        "Instruction TLB: 4 KByte pages, 4-way set associative, 32 entries\n" },
    { 0x02, TLB,        "Instruction TLB: 4 MByte pages, fully associative, 2 entries\n" },
    { 0x03, TLB,        "Data TLB: 4 KByte pages, 4-way set associative, 64 entries\n" },
    { 0x04, TLB,        "Data TLB: 4 MByte pages, 4-way set associative, 8 entries\n" },
    { 0x05, TLB,        "Data TLB1: 4 MByte pages, 4-way set associative, 32 entries\n" },
    { 0x06, CACHE,      "1st-level instruction cache: 8 KBytes, 4-way set associative, 32 byte line size\n" },
    { 0x08, CACHE,      "1st-level instruction cache: 16 KBytes, 4-way set associative, 32 byte line size\n" },
    { 0x09, CACHE,      "1st-level instruction cache: 32KBytes, 4-way set associative, 64 byte line size\n" },
    { 0x0A, CACHE,      "1st-level data cache: 8 KBytes, 2-way set associative, 32 byte line size\n" },
    { 0x0B, TLB,        "Instruction TLB: 4 MByte pages, 4-way set associative, 4 entries\n" },
    { 0x0C, CACHE,      "1st-level data cache: 16 KBytes, 4-way set associative, 32 byte line size\n" },
    { 0x0D, CACHE,      "1st-level data cache: 16 KBytes, 4-way set associative, 64 byte line size\n" },
    { 0x0E, CACHE,      "1st-level data cache: 24 KBytes, 6-way set associative, 64 byte line size\n" },
    { 0x1D, CACHE,      "2nd-level cache: 128 KBytes, 2-way set associative, 64 byte line size\n" },
    { 0x21, CACHE,      "2nd-level cache: 256 KBytes, 8-way set associative, 64 byte line size\n" },
    { 0x22, CACHE,      "3rd-level cache: 512 KBytes, 4-way set associative, 64 byte line size, 2 lines per sector\n" },
    { 0x23, CACHE,      "3rd-level cache: 1 MBytes, 8-way set associative, 64 byte line size, 2 lines per sector\n" },
    { 0x24, CACHE,      "2nd-level cache: 1 MBytes, 16-way set associative, 64 byte line size\n" },
    { 0x25, CACHE,      "3rd-level cache: 2 MBytes, 8-way set associative, 64 byte line size, 2 lines per sector\n" },
    { 0x29, CACHE,      "3rd-level cache: 4 MBytes, 8-way set associative, 64 byte line size, 2 lines per sector\n" },
    { 0x2C, CACHE,      "1st-level data cache: 32 KBytes, 8-way set associative, 64 byte line size\n" },
    { 0x30, CACHE,      "1st-level instruction cache: 32 KBytes, 8-way set associative, 64 byte line size\n" },
    { 0x40, MISSING,    "No 2nd-level cache or, if processor contains a valid 2nd-level cache, no 3rd-level cache\n" },
    { 0x41, CACHE,      "2nd-level cache: 128 KBytes, 4-way set associative, 32 byte line size\n" },
    { 0x42, CACHE,      "2nd-level cache: 256 KBytes, 4-way set associative, 32 byte line size\n" },
    { 0x43, CACHE,      "2nd-level cache: 512 KBytes, 4-way set associative, 32 byte line size\n" },
    { 0x44, CACHE,      "2nd-level cache: 1 MByte, 4-way set associative, 32 byte line size\n" },
    { 0x45, CACHE,      "2nd-level cache: 2 MByte, 4-way set associative, 32 byte line size\n" },
    { 0x46, CACHE,      "3rd-level cache: 4 MByte, 4-way set associative, 64 byte line size\n" },
    { 0x47, CACHE,      "3rd-level cache: 8 MByte, 8-way set associative, 64 byte line size\n" },
    { 0x48, CACHE,      "2nd-level cache: 3MByte, 12-way set associative, 64 byte line size\n" },
    { 0x49, CACHE,      "3rd-level cache: 4MB, 16-way set associative, 64-byte line size (Intel Xeon processor MP, Family 0FH, Model 06H). 2nd-level cache: 4 MByte, 16-way set associative, 64 byte line size\n" },
    { 0x4A, CACHE,      "3rd-level cache: 6MByte, 12-way set associative, 64 byte line size\n" },
    { 0x4B, CACHE,      "3rd-level cache: 8MByte, 16-way set associative, 64 byte line size\n" },
    { 0x4C, CACHE,      "3rd-level cache: 12MByte, 12-way set associative, 64 byte line size\n" },
    { 0x4D, CACHE,      "3rd-level cache: 16MByte, 16-way set associative, 64 byte line size\n" },
    { 0x4E, CACHE,      "2nd-level cache: 6MByte, 24-way set associative, 64 byte line size\n" },
    { 0x4F, TLB,        "Instruction TLB: 4 KByte pages, 32 entries\n" },
    { 0x50, TLB,        "Instruction TLB: 4 KByte and 2-MByte or 4-MByte pages, 64 entries\n" },
    { 0x51, TLB,        "Instruction TLB: 4 KByte and 2-MByte or 4-MByte pages, 128 entries\n" },
    { 0x52, TLB,        "Instruction TLB: 4 KByte and 2-MByte or 4-MByte pages, 256 entries\n" },
    { 0x55, TLB,        "Instruction TLB: 2-MByte or 4-MByte pages, fully associative, 7 entries\n" },
    { 0x56, TLB,        "Data TLB0: 4 MByte pages, 4-way set associative, 16 entries\n" },
    { 0x57, TLB,        "Data TLB0: 4 KByte pages, 4-way associative, 16 entries\n" },
    { 0x59, TLB,        "Data TLB0: 4 KByte pages, fully associative, 16 entries\n" },
    { 0x5A, TLB,        "Data TLB0: 2 MByte or 4 MByte pages, 4-way set associative, 32 entries\n" },
    { 0x5B, TLB,        "Data TLB: 4 KByte and 4 MByte pages, 64 entries\n" },
    { 0x5C, TLB,        "Data TLB: 4 KByte and 4 MByte pages,128 entries\n" },
    { 0x5D, TLB,        "Data TLB: 4 KByte and 4 MByte pages,256 entries\n" },
    { 0x60, CACHE,      "1st-level data cache: 16 KByte, 8-way set associative, 64 byte line size\n" },
    { 0x61, TLB,        "Instruction TLB: 4 KByte pages, fully associative, 48 entries\n" },
    { 0x63, TLB,        "Data TLB: 2 MByte or 4 MByte pages, 4-way set associative, 32 entries and a separate array with 1 GByte pages, 4-way set associative, 4 entries\n" },
    { 0x64, TLB,        "Data TLB: 4 KByte pages, 4-way set associative, 512 entries\n" },
    { 0x66, CACHE,      "1st-level data cache: 8 KByte, 4-way set associative, 64 byte line size\n" },
    { 0x67, CACHE,      "1st-level data cache: 16 KByte, 4-way set associative, 64 byte line size\n" },
    { 0x68, CACHE,      "1st-level data cache: 32 KByte, 4-way set associative, 64 byte line size\n" },
    { 0x6A, TLB,        "uTLB: 4 KByte pages, 8-way set associative, 64 entries\n" },
    { 0x6B, TLB,        "DataTLB: 4 KByte pages, 8-way set associative, 256 entries\n" },
    { 0x6C, TLB,        "DataTLB: 2M/4M pages, 8-way set associative, 128 entries\n" },
    { 0x6D, TLB,        "DataTLB: 1 GByte pages, fully associative, 16 entries\n" },
    { 0x70, CACHE,      "Trace cache: 12 K-uop, 8-way set associative\n" },
    { 0x71, CACHE,      "Trace cache: 16 K-uop, 8-way set associative\n" },
    { 0x72, CACHE,      "Trace cache: 32 K-uop, 8-way set associative\n" },
    { 0x76, TLB,        "Instruction TLB: 2M/4M pages, fully associative, 8 entries\n" },
    { 0x78, CACHE,      "2nd-level cache: 1 MByte, 4-way set associative, 64byte line size\n" },
    { 0x79, CACHE,      "2nd-level cache: 128 KByte, 8-way set associative, 64 byte line size, 2 lines per sector\n" },
    { 0x7A, CACHE,      "2nd-level cache: 256 KByte, 8-way set associative, 64 byte line size, 2 lines per sector\n" },
    { 0x7B, CACHE,      "2nd-level cache: 512 KByte, 8-way set associative, 64 byte line size, 2 lines per sector\n" },
    { 0x7C, CACHE,      "2nd-level cache: 1 MByte, 8-way set associative, 64 byte line size, 2 lines per sector\n" },
    { 0x7D, CACHE,      "2nd-level cache: 2 MByte, 8-way set associative, 64byte line size\n" },
    { 0x7F, CACHE,      "2nd-level cache: 512 KByte, 2-way set associative, 64-byte line size\n" },
    { 0x80, CACHE,      "2nd-level cache: 512 KByte, 8-way set associative, 64-byte line size\n" },
    { 0x82, CACHE,      "2nd-level cache: 256 KByte, 8-way set associative, 32 byte line size\n" },
    { 0x83, CACHE,      "2nd-level cache: 512 KByte, 8-way set associative, 32 byte line size\n" },
    { 0x84, CACHE,      "2nd-level cache: 1 MByte, 8-way set associative, 32 byte line size\n" },
    { 0x85, CACHE,      "2nd-level cache: 2 MByte, 8-way set associative, 32 byte line size\n" },
    { 0x86, CACHE,      "2nd-level cache: 512 KByte, 4-way set associative, 64 byte line size\n" },
    { 0x87, CACHE,      "2nd-level cache: 1 MByte, 8-way set associative, 64 byte line size\n" },
    { 0xA0, TLB,        "DataTLB: 4k pages, fully associative, 32 entries\n" },
    { 0xB0, TLB,        "Instruction TLB: 4 KByte pages, 4-way set associative, 128 entries\n" },
    { 0xB1, TLB,        "Instruction TLB: 2M pages, 4-way, 8 entries or 4M pages, 4-way, 4 entries\n" },
    { 0xB2, TLB,        "Instruction TLB: 4KByte pages, 4-way set associative, 64 entries\n" },
    { 0xB3, TLB,        "Data TLB: 4 KByte pages, 4-way set associative, 128 entries\n" },
    { 0xB4, TLB,        "Data TLB1: 4 KByte pages, 4-way associative, 256 entries\n" },
    { 0xB5, TLB,        "Instruction TLB: 4KByte pages, 8-way set associative, 64 entries\n" },
    { 0xB6, TLB,        "Instruction TLB: 4KByte pages, 8-way set associative, 128 entries\n" },
    { 0xBA, TLB,        "Data TLB1: 4 KByte pages, 4-way associative, 64 entries\n" },
    { 0xC0, TLB,        "Data TLB: 4 KByte and 4 MByte pages, 4-way associative, 8 entries\n" },
    { 0xC1, TLB,        "Shared 2nd-Level TLB: 4 KByte/2MByte pages, 8-way associative, 1024 entries\n" },
    { 0xC2, TLB,        "DataTLB: 4 KByte/2 MByte pages, 4-way associative, 16 entries\n" },
    { 0xC3, TLB,        "Shared 2nd-Level TLB: 4 KByte /2 MByte pages, 6-way associative, 1536 entries. Also 1GBbyte pages, 4-way, 16 entries.\n" },
    { 0xC4, TLB,        "DataTLB: 2M/4M Byte pages, 4-way associative, 32 entries\n" },
    { 0xCA, TLB,        "Shared 2nd-Level TLB: 4 KByte pages, 4-way associative, 512 entries\n" },
    { 0xD0, CACHE,      "3rd-level cache: 512 KByte, 4-way set associative, 64 byte line size\n" },
    { 0xD1, CACHE,      "3rd-level cache: 1 MByte, 4-way set associative, 64 byte line size\n" },
    { 0xD2, CACHE,      "3rd-level cache: 2 MByte, 4-way set associative, 64 byte line size\n" },
    { 0xD6, CACHE,      "3rd-level cache: 1 MByte, 8-way set associative, 64 byte line size\n" },
    { 0xD7, CACHE,      "3rd-level cache: 2 MByte, 8-way set associative, 64 byte line size\n" },
    { 0xD8, CACHE,      "3rd-level cache: 4 MByte, 8-way set associative, 64 byte line size\n" },
    { 0xDC, CACHE,      "3rd-level cache: 1.5 MByte, 12-way set associative, 64 byte line size\n" },
    { 0xDD, CACHE,      "3rd-level cache: 3 MByte, 12-way set associative, 64 byte line size\n" },
    { 0xDE, CACHE,      "3rd-level cache: 6 MByte, 12-way set associative, 64 byte line size\n" },
    { 0xE2, CACHE,      "3rd-level cache: 2 MByte, 16-way set associative, 64 byte line size\n" },
    { 0xE3, CACHE,      "3rd-level cache: 4 MByte, 16-way set associative, 64 byte line size\n" },
    { 0xE4, CACHE,      "3rd-level cache: 8 MByte, 16-way set associative, 64 byte line size\n" },
    { 0xEA, CACHE,      "3rd-level cache: 12MByte, 24-way set associative, 64 byte line size\n" },
    { 0xEB, CACHE,      "3rd-level cache: 18MByte, 24-way set associative, 64 byte line size\n" },
    { 0xEC, CACHE,      "3rd-level cache: 24MByte, 24-way set associative, 64 byte line size\n" },
    { 0xF0, PREFETCH,   "64-Byte prefetching\n" },
    { 0xF1, PREFETCH,   "128-Byte prefetching\n" },
    { 0xFF, NOREPORT,   "CPUID leaf 2 does not report cache descriptor information, use CPUID leaf 4 to query cache parameters\n" }
};

void cpuid()
{
    __asm__ __volatile__("cpuid;"
                         : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
                         : "a"(eax));
}

void cpuid_with_ecx()
{
    __asm__ __volatile__("cpuid;"
                         : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
                         : "a"(eax), "c"(ecx));
}

cpuid_cache_info* cache_info_lookup(unsigned char desc)
{
    unsigned int table_size = sizeof(cpuid_cache_info_table) /
                  sizeof(cpuid_cache_info);
    for (int i = 1; i < table_size; ++i) {
        if (desc == cpuid_cache_info_table[i].CacheDescriptor) {
            return &cpuid_cache_info_table[i];
        }
    }
    return NULL;
}

int main(int argc, char **argv)
{
    char cache_info[255]    = "";
    char tlb_info[255]      = "";
    char prefetch_info[255] = "";
    bool no_report = false;

    eax = 0x02;
    cpuid();
    for (int i = 0; i < 4; ++i) {   /* register */
        /* printf("Register %d: 0x%08X\n", (i + 1), *(registers[i])); */
        if (((*registers[i] >> 31) & 0b1) == 1) {
            continue;
        }
        for (int j = 0; j < 4; ++j) {   /* byte in register */
            if ((i == 0) && (j == 3)) {
                continue;
            }
            unsigned char byte = ((*registers[i]) >> (24 - (j * 8))) & 0xFF;
            /* printf("Byte %d:     0x%02X\n", (j + 1), byte); */
            cpuid_cache_info* info = cache_info_lookup(byte);
            if (info == NULL) {
                continue;
            }
            switch (info->Type) {
            case CACHE:
                strcat(cache_info, info->Description);
                break;
            case TLB:
                strcat(tlb_info, info->Description);
                break;
            case PREFETCH:
                strcat(prefetch_info, info->Description);
            case NOREPORT:
                no_report = true;
            }
        }
    }
    if (no_report) {
        eax = 0x04;
        unsigned int index = 0;
        ecx = index;
        cpuid_with_ecx();
        while ((eax & 0b11111) != 0) {
            unsigned int cache_type_val = (eax & 0b11111);
            char cache_type[50];
            switch (cache_type_val) {
            case 1:
                strcpy(cache_type, "data cache");
                break;
            case 2:
                strcpy(cache_type, "instruction cache");
                break;
            case 3:
                strcpy(cache_type, "unified cache");
                break;
            default:
                strcpy(cache_type, "reserved");
            }
            unsigned int cache_level = ((eax >> 5) & 0b111);
            unsigned int line_size = (ebx & 0xFFF) + 1;
            unsigned int partitions = ((ebx >> 12) & 0x3FF) + 1;
            unsigned int ways = ((ebx >> 22) & 0x3FF) + 1;
            unsigned int sets = ecx + 1;
            unsigned int cache_mag = 0;
            unsigned long long tmp = ways * partitions;
            while (tmp > 4294967296) {
                tmp = tmp / 1024;
                cache_mag++;
            }
            tmp = tmp * line_size;
            while (tmp > 4294967296) {
                tmp = tmp / 1024;
                cache_mag++;
            }
            tmp = tmp * sets;
            while (tmp >= 1024) {
                tmp = tmp / 1024;
                cache_mag++;
            }
            unsigned int cache_size = tmp;
            char mag_string[20];
            switch (cache_mag)
            {
            case 0:
                strcpy(mag_string, "Byte");
                break;
            case 1:
                strcpy(mag_string, "KByte");
                break;
            case 2:
                strcpy(mag_string, "MByte");
                break;
            case 3:
                strcpy(mag_string, "GByte");
                break;
            }
            printf("Level %d %s: %d %s, %d ways, %d partitions, %d line size, %d sets\n",
                   cache_level, 
                   cache_type, 
                   cache_size, 
                   mag_string, 
                   ways, 
                   partitions, 
                   line_size, 
                   sets);
            eax = 0x04;
            index++;
            ecx = index;
            cpuid_with_ecx();
        }
    }
    else {
        printf("%s", cache_info);
    }
    printf("%s%s", tlb_info, prefetch_info);
    eax = 0x80000008;
    cpuid();
    unsigned int physical_address_size = (eax & 0xFF);
    printf("Physical Address Size: %d bits\n", physical_address_size);
    unsigned int linear_address_size = ((eax >> 8) & 0xFF);
    printf("Linear Address Size: %d bits\n", linear_address_size);

    eax = 0xB;
    ecx = 0x1;
    cpuid_with_ecx();
    unsigned int logical_cores = (ebx & 0xFFFF);
    printf("Logical Cores: %d\n", logical_cores);

    eax = 0x1;
    cpuid();
    unsigned int family = ((eax >> 8) & 0xF);
    unsigned int model = ((eax >> 4) & 0xF);
    unsigned int extended_model = ((eax >> 16) & 0xF);
    unsigned int extended_family = ((eax >> 20) & 0xFF);
    if (family == 15) {
        family += extended_family;
        model += (extended_model << 4);
    }
    else if (family == 6) {
        model += (extended_model << 4);
    }
    printf("Family: %d\n", family);
    printf("Model Number: %d\n", model);

    eax = 0x80000000;
    cpuid();
    if (eax >= 0x80000004) {
        char model_name[48];
        for (int i = 0; i < 4; ++i) {
            eax = 0x80000002 + i;
            cpuid();
            for (int j = 0; j < 4; ++j) {
                memcpy(model_name + (i * 16) + (j * 4), (char*)registers[j], 4);
            }
        }
        printf("Model Name: %s\n", model_name);
    }
	
    eax = 0x16;
    cpuid();
    if ((eax & 0xFFFF) != 0)
        printf("CPU Frequency: %d MHz\n", (eax & 0xFFFF));
    else
        printf("CPU frequency reporting not supported\n");

    eax = 0x1;
    cpuid();
    char* cpu_features_d[32] = {
        "Onboard x87 FPU\n",
        "Virtual 8086 mode extensions\n",
        "Debugging extensions\n",
        "Page Size Extension\n",
        "Time Stamp Counter\n",
        "Model-specific registers\n",
        "Machine Check Exception\n",
        "Physical Address Extension\n",
        "CMPXCHG8\n",
        "Onboard Advanced Programmable Interrupt Controller\n",
        "",
        "SYSENTER and SYSEXIT instructions\n",
        "Memory Type Range Registers\n",
        "Page Global Enable bit in CR4\n",
        "Machine check architecture\n",
        "Conditional move and FCMOV instructions\n",
        "Page Attribute Table\n",
        "36-bit page size extension\n",
        "Processor Serial Number\n",
        "CLFLUSH instruction\n",
        "",
        "Debug store\n",
        "Onboard thermal control MSRs for ACPI\n",
        "MMX instructions\n",
        "FXSAVE, FXRESTOR instructions\n",
        "SSE instructions\n",
        "SSE2 instructions\n",
        "CPU cache supports self-snoop\n",
        "Hyper-threading\n",
        "Thermal monitor automatically limits temperature\n",
        "IA64 processor emulating x86\n",
        "Pending Break Enable wakeup support\n"
    };
    char* cpu_features_c[32] = {
        "SSE3 instructions\n",
        "PCLMULQDQ support\n",
        "64-bit debug store\n",
        "MONITOR and MWAIT instructions\n",
        "CPL qualified debug store\n",
        "Virtual Machine eXtensions\n",
        "Safer Mode Extensions\n",
        "Enhanced SpeedStep\n",
        "Thermal Monitor 2\n",
        "SSSE3 instructions\n",
        "L1 Context ID\n",
        "Silicon Debug interface\n",
        "Fused multiply-add 3\n",
        "CMPXCHG16B instruction\n",
        "Can disable sending task priority messages\n",
        "Perfmon & debug capability\n",
        "",
        "Process context identifiers\n",
        "Direct cache access for DMA writes\n",
        "SSE4.1 instructions\n",
        "SSE4.2 instructions\n",
        "x2APIC support\n",
        "MOVBE instruction\n",
        "POPCNT instruction\n",
        "APIC supports one-shot operation using a TSC deadline value\n",
        "AES instruction set\n",
        "XSAVE, XRESTOR, XSETBV, XGETBV\n",
        "XSAVE enabled by OS\n",
        "Advanced Vector Extensions\n",
        "Half precision float support\n",
        "RDRAND\n",
        "Running on a hypervisor\n"
    };
    printf("CPU Features:\n");
    for (int i = 0; i < 32; ++i) {
        if (ecx & 0x1)
            printf("\t%s", cpu_features_c[i]);
        ecx = (ecx >> 1);
    }
    for (int i = 0; i < 32; ++i) {
        if (edx & 0x1)
            printf("\t%s", cpu_features_d[i]);
        edx = (edx >> 1);
    }
    eax = 0x7;
    cpuid();
    char* ext_cpu_features_b[32] = {
        "Access to base of fs and gs\n",
        "Virtual 8086 mode extensions\n",
        "Software Guard Extensions\n",
        "Bit Manipulation Instruction Set 1\n",
        "Transactional Synchronization Extensions\n",
        "Advanced Vector Extensions 2\n",
        "",
        "Supervisor-Mode Execution Prevention\n",
        "Bit Manipulation Instruction Set 2\n",
        "Enhanced REP MOVSB/STOSB\n",
        "INVPCID instruction\n",
        "Transactional Synchronization Extensions\n",
        "Platform Quality of Service Monitoring\n",
        "FPU CS and FPU DS deprecated\n",
        "Intel MPX\n",
        "Platform Quality of Service Enforcement\n",
        "AVX-512 Foundation\n",
        "AVX-512 Doubleword and Quadword Instructions\n",
        "RDSEED instruction\n",
        "Intel ADX\n",
        "Supervisor Mode Access Prevention\n",
        "AVX-512 Integer Fused Multiply-Add Instructions\n",
        "PCOMMIT instruction\n",
        "CLFLUSHOPT instruction\n",
        "CLWB instruction\n",
        "Intel Processor Trace\n",
        "AVX-512 Prefetch Instructions\n",
        "AVX-512 Exponential and Reciprocal Instructions\n",
        "AVX-512 Conflict Detection Instructions\n",
        "Intel SHA extensions\n",
        "AVX-512 Byte and Word Instructions\n",
        "AVX-512 Vector Length Extensions\n"
    };
    char* ext_cpu_features_c[32] = {
        "PREFETCHWT1 instruction\n",
        "AVX-512 Vector Bit Manipulation Instructions\n",
        "User-mode Instruction Prevention\n",
        "Memory Protection Keys for User-mode pages\n",
        "PKU enabled by OS\n",
        "","","","","","","","","",
        "AVX-512 Vector Population Count D/Q\n",
        "","","","","","","",
        "Read Processor ID\n",
        "","","","","","","",
        "SGX Launch Configuration\n",
        ""
    };
    for (int i = 0; i < 32; ++i) {
        if (ecx & 0x1)
            printf("\t%s", ext_cpu_features_b[i]);
        ecx = (ecx >> 1);
    }
    for (int i = 0; i < 32; ++i) {
        if (edx & 0x1)
            printf("\t%s", ext_cpu_features_c[i]);
        edx = (edx >> 1);
    }
    if (edx & 0b10)
        printf("\tAVX-512 Neural Network Instructions\n");
    if (edx & 0b11)
        printf("\tAVX-512 Multiply Accumulation Single precision\n");

	return 0;
}
