#include <stdio.h>
#include <inttypes.h>
#include <cpuinfo.h>

/* ------------------------
 * Architecture detection
 * ------------------------ */
static const char* arch_name(void)
{
#if defined(CPUINFO_ARCH_X86) || defined(CPUINFO_ARCH_X86_64)
    return "x86";
#elif defined(CPUINFO_ARCH_ARM)
    return "arm";
#elif defined(CPUINFO_ARCH_ARM64)
    return "aarch64";
#elif defined(CPUINFO_ARCH_RISCV32) || defined(CPUINFO_ARCH_RISCV64)
    return "riscv";
#else
    return "unknown";
#endif
}

/* ------------------------
 * Cache printing
 * ------------------------ */
static void print_cache(const char* name, const struct cpuinfo_cache* c)
{
    if (!c) return;

    printf("  %-3s : %6" PRIu32 " KB, %2" PRIu32 "-way, line=%" PRIu32 " bytes\n",
           name,
           (uint32_t)(c->size / 1024),
           (uint32_t)c->associativity,
           (uint32_t)c->line_size);
}

int main(void)
{
    if (!cpuinfo_initialize()) {
        fprintf(stderr, "cpuinfo_initialize() failed\n");
        return 1;
    }

    printf("General:\n");
    printf("  Architecture : %s\n", arch_name());

    printf("  Packages     : %" PRIu32 "\n", cpuinfo_get_packages_count());
    printf("  Cores        : %" PRIu32 "\n", cpuinfo_get_cores_count());
    printf("  Logical CPUs : %" PRIu32 "\n", cpuinfo_get_processors_count());

    printf("\nTopology:\n");
    printf("  Clusters     : %" PRIu32 "\n", cpuinfo_get_clusters_count());
    printf("  Uarch types  : %" PRIu32 "\n", cpuinfo_get_uarchs_count());

    printf("\nCache hierarchy (first instance of each level):\n");
    if (cpuinfo_get_l1d_caches_count()) print_cache("L1d", cpuinfo_get_l1d_cache(0));
    if (cpuinfo_get_l1i_caches_count()) print_cache("L1i", cpuinfo_get_l1i_cache(0));
    if (cpuinfo_get_l2_caches_count())  print_cache("L2",  cpuinfo_get_l2_cache(0));
    if (cpuinfo_get_l3_caches_count())  print_cache("L3",  cpuinfo_get_l3_cache(0));
    if (cpuinfo_get_l4_caches_count())  print_cache("L4",  cpuinfo_get_l4_cache(0));

    printf("\nPackages:\n");
    for (uint32_t i = 0; i < cpuinfo_get_packages_count(); ++i) {
        const struct cpuinfo_package* pkg = cpuinfo_get_package(i);
        printf("  Package %u: %s\n", i, pkg->name ? pkg->name : "(unknown)");
    }

    printf("\nPer logical CPU:\n");
    for (uint32_t i = 0; i < cpuinfo_get_processors_count(); ++i) {
        const struct cpuinfo_processor* p = cpuinfo_get_processor(i);
        const struct cpuinfo_core* core = p->core;
        const struct cpuinfo_cluster* cluster = core->cluster;

        printf("  CPU %2u | core=%2u | cluster=%2u\n", i, core->core_id, cluster->cluster_id);
    }

    cpuinfo_deinitialize();
}
