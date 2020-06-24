#include "printlengthparam.h"
#include "printesc.h"
#include "print.h"

void printlengthparam(int n)
{
	switch (n)
	{
		case par_indent_code:
			printesc("parindent");
			break;
		case math_surround_code:
			printesc("mathsurround");
			break;
		case line_skip_limit_code:
			printesc("lineskiplimit");
			break;
		case hsize_code:
			printesc("hsize");
			break;
		case vsize_code:
			printesc("vsize");
			break;
		case max_depth_code:
			printesc("maxdepth");
			break;
		case split_max_depth_code:
			printesc("splitmaxdepth");
			break;
		case box_max_depth_code:
			printesc("boxmaxdepth");
			break;
		case hfuzz_code:
			printesc("hfuzz");
			break;
		case vfuzz_code:
			printesc("vfuzz");
			break;
		case delimiter_shortfall_code:
			printesc("delimitershortfall");
			break;
		case null_delimiter_space_code:
			printesc("nulldelimiterspace");
			break;
		case script_space_code:
			printesc("scriptspace");
			break;
		case pre_display_size_code:
			printesc("predisplaysize");
			break;
		case display_width_code:
			printesc("displaywidth");
			break;
		case display_indent_code:
			printesc("displayindent");
			break;
		case overfull_rule_code:
			printesc("overfullrule");
			break;
		case hang_indent_code:
			printesc("hangindent");
			break;
		case h_offset_code:
			printesc("hoffset");
			break;
		case v_offset_code:
			printesc("voffset");
			break;
		case emergency_stretch_code:
			printesc("emergencystretch");
			break;
		default:
			print("[unknown dimen parameter!]");
	}
}
