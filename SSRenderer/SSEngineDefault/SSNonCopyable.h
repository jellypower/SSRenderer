#pragma once

class SSNoncopyable
{
public:
	SSNoncopyable() = default;
	SSNoncopyable(const SSNoncopyable& rhs) = delete;
	SSNoncopyable& operator=(const SSNoncopyable& rhs) = delete;
};
