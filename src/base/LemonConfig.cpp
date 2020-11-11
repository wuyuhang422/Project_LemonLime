/*
 * SPDX-FileCopyrightText: 2020  Project LemonLime
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include "LemonConfig.hpp"
//
#include "base/LemonUtils.hpp"
#include "base/compiler.h"

namespace Lemon::base::config {

	void LemonConfigJudge::read(const QJsonObject &json) {
		READ_JSON_INT(defaultFullScore)
		READ_JSON_INT(defaultTimeLimit)
		READ_JSON_INT(defaultMemoryLimit)
		READ_JSON_INT(compileTimeLimit)
		READ_JSON_INT(specialJudgeTimeLimit)
		READ_JSON_INT(fileSizeLimit)
		READ_JSON_INT(rejudgeTimes)

		READ_JSON_STR(defaultInputFileExtension)
		READ_JSON_STR(defaultOutputFileExtension)
		READ_JSON_STR(diffPath)

		READ_JSON_STRLIST(inputFileExtensions)
		READ_JSON_STRLIST(outputFileExtensions)
		READ_JSON_STRLIST(recentContest)

		// CompilerList
		if (json.contains("compilerList") && json["compilerList"].isArray()) {
			QJsonArray _compilerList = json["compilerList"].toArray();
			compilerList.clear();
			compilerList.reserve(_compilerList.size());
			for (int compilerIndex = 0; compilerIndex < _compilerList.size(); ++compilerIndex) {
				QJsonObject compilerObject = _compilerList[compilerIndex].toObject();
				Compiler *compiler = new Compiler;
				compiler->read(compilerObject);
				compilerList.append(compiler);
			}
		}
	}

	void LemonConfigJudge::write(QJsonObject &json) const {
		WRITE_JSON(defaultFullScore)
		WRITE_JSON(defaultTimeLimit)
		WRITE_JSON(defaultMemoryLimit)
		WRITE_JSON(compileTimeLimit)
		WRITE_JSON(specialJudgeTimeLimit)
		WRITE_JSON(fileSizeLimit)
		WRITE_JSON(rejudgeTimes)

		WRITE_JSON(defaultInputFileExtension)
		WRITE_JSON(defaultOutputFileExtension)
		WRITE_JSON(diffPath)

		WRITE_JSON_STRLIST(inputFileExtensions)
		WRITE_JSON_STRLIST(outputFileExtensions)
		WRITE_JSON_STRLIST(recentContest)

		QJsonArray _compilerList;
		for (const auto &compiler : compilerList) {
			QJsonObject compilerObject;
			compiler->write(compilerObject);
			_compilerList.append(compilerObject);
		}
		json["compilerList"] = _compilerList;
	}

	void LemonConfigUI::read(const QJsonObject &json) {
		READ_JSON_STR(language)
		READ_JSON_STR(theme)
	}

	void LemonConfigUI::write(QJsonObject &json) const {
		WRITE_JSON(language)
		WRITE_JSON(theme)
	}

	void LemonConfig::read(const QJsonObject &json) {
		READ_JSON_OBJECT(judgeConfig)
		READ_JSON_OBJECT(uiConfig)

		READ_JSON_INT(splashTime)
	}

	void LemonConfig::write(QJsonObject &json) const {
		WRITE_JSON_OBJECT(judgeConfig)
		WRITE_JSON_OBJECT(uiConfig)

		WRITE_JSON(splashTime)
	}

	auto LemonConfig::loadConfig(SaveFormat saveFormat) -> bool {}

	auto LemonConfig::saveConfig(SaveFormat saveFormat) const -> bool {}

} // namespace Lemon::base::config
