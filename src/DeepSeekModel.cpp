#include "DeepSeekModel.h"

std::string inx::DeepSeek::ModelToString(inx::DeepSeek::Model model)
{
	switch (model) {
	case inx::DeepSeek::Model::DeepSeekChat:
		return "deepseek-chat";
	case inx::DeepSeek::Model::DeepSeekReasoner:
		return "deepseek-reasoner";
	default: // only adding this to avoid compiler warnings
		return "deepseek-chat";
	}
}