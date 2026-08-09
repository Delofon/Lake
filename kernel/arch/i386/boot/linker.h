#ifndef LINKER_H_
#define LINKER_H_

// Exposed by linker.ld

extern const void lake_lma_start;
extern const void lake_lma_end;

extern const void lake_vla_start;
extern const void lake_vla_end;

extern const void sbss;
extern const void ebss;

static const void *svlake = &lake_vla_start;
static const void *evlake = &lake_vla_end;

static const void *sllake = &lake_lma_start;
static const void *ellake = &lake_lma_end;

static const void *svbss = &sbss;
static const void *evbss = &ebss;

static const up usvlake = (up)&lake_vla_start;
static const up uevlake = (up)&lake_vla_end;

static const up usllake = (up)&lake_lma_start;
static const up uellake = (up)&lake_lma_end;

static const up usvbss = (up)&sbss;
static const up uevbss = (up)&ebss;

#endif

