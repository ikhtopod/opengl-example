#pragma once

#ifndef JUSTUTILITY_H
#define JUSTUTILITY_H

namespace JustUtility {

enum AttribIndex : GLuint {
	POSITION,
	TEXTURE,
};

template <typename T>
static void CopyVector(const std::vector<T>& from, std::vector<T>& to) {
	to.clear();
	to.resize(from.size());
	std::copy(from.cbegin(), from.cend(), to.begin());
}

} // namespace JustUtility

#endif // !JUSTUTILITY_H
