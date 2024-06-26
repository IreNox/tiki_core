#pragma once

namespace tiki
{
	template< class TKey, class TValue >
	struct Pair
	{
		using KeyType = TKey;
		using ValueType = TValue;

		TKey	key;
		TValue	value;
	};
}
