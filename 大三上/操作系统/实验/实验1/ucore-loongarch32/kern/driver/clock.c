#include <loongarch.h>
#include <asm/loongisa_csr.h>
#include <trap.h>
#include <stdio.h>
#include <picirq.h>
//#include <sched.h>

volatile size_t ticks;


#define HZ 100

static void reload_timer()
{
  write_csr_tmintclear(CSR_TMINTCLR_TI);
}

int clock_int_handler(void * data)
{
#ifdef LAB1_EX2
  // LAB1 EXERCISE2: YOUR CODE
  // (1) count ticks here
  ticks ++;
#ifdef _SHOW_100_TICKS
  // (2) if ticks % 100 == 0 then call kprintf to print "100 ticks"
  if (ticks % 100 == 0) {
    kprintf("100 ticks\n");
  }
#endif
#endif
#ifdef LAB4_EX1
  run_timer_list();
#endif
  reload_timer();
  return 0;
}

void
clock_init(void) {
  // setup timer
  unsigned long timer_config;
  unsigned long period = 200000000;
  period = period / HZ;
  timer_config = period & LISA_CSR_TMCFG_TIMEVAL;
  timer_config |= (LISA_CSR_TMCFG_PERIOD | LISA_CSR_TMCFG_EN);
  __csrwr(timer_config, LISA_CSR_TMCFG);
  pic_enable(TIMER0_IRQ);
  kprintf("++setup timer interrupts\n");
}

