#ifndef	CONFIG_TYPE_POINTER_H
#define	CONFIG_TYPE_POINTER_H

#include <map>

#include <config/config_object.h>
#include <config/config_type.h>

class ConfigValue;

class ConfigTypePointer : public ConfigType {
	std::map<ConfigValue *, ConfigObject *> pointers_;
public:
	ConfigTypePointer(void)
	: ConfigType("pointer"),
	  pointers_()
	{ }

	~ConfigTypePointer()
	{
		pointers_.clear();
	}

	template<typename T>
	bool get(ConfigValue *cv, ConfigObject **cop, T **ccp) const
	{
		std::map<ConfigValue *, ConfigObject *>::const_iterator it;

		it = pointers_.find(cv);
		if (it == pointers_.end())
			return (false);

		ConfigObject *co = it->second;
		if (co == NULL) {
			*cop = NULL;
			*ccp = NULL;
			return (true);
		}

		T *cc = co->coerce<T>();
		if (cc == NULL)
			return (false);

		*cop = co;
		*ccp = cc;

		return (true);
	}

	bool set(ConfigValue *, const std::string&);
};

extern ConfigTypePointer config_type_pointer;

#endif /* !CONFIG_TYPE_POINTER_H */