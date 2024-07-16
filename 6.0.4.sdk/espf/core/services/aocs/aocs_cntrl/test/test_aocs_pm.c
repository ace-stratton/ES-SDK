

#include "unity.h"



#include "mock_debug.h"
#include "mock_cmsis_os.h"
#include "mock_cmsis_os2.h"
#include "mock_es_exeh.h"
#include "mock_projdefs.h"
#include "mock_FreeRTOSConfig.h"
#include "mock_es_cdef.h"
#include "mock_libqueue.h"
#include "mock_nvm.h"
#include "mock_SdMngr.h"
#include "mock_datetime.h"
#include "aocs_pm.h"


void setUp(void)
{
}

void tearDown(void)
{
}

void test_aocs_pm_assess_stability_fail(void)
{
	aocs_pm_ctx_t test_ctx;

	uint8_t res=0;
	test_ctx.f_lower_threshold = 0.95;
	test_ctx.f_upper_threshold = 1.05;
	test_ctx.s_threshold_values.f_tolerance = 1;
	test_ctx.s_threshold_values.f_safety_factor = 0.05;
	test_ctx.data = 2.0;
	res = fs_aocs_pm_assess_stability(&test_ctx);
	TEST_ASSERT_EQUAL_UINT8(0, res);
//    TEST_IGNORE_MESSAGE("Need to Implement aocs_pm");
}

void test_aocs_pm_assess_stability_pass(void)
{
	aocs_pm_ctx_t test_ctx;

	uint8_t res=0;
	test_ctx.f_lower_threshold = 0.95;
	test_ctx.f_upper_threshold = 1.05;
	test_ctx.s_threshold_values.f_tolerance = 1;
	test_ctx.s_threshold_values.f_safety_factor = 0.05;
	test_ctx.data = 1.0;
	res = fs_aocs_pm_assess_stability(&test_ctx);
	TEST_ASSERT_EQUAL_UINT8(1, res);
//    TEST_IGNORE_MESSAGE("Need to Implement aocs_pm");
}



