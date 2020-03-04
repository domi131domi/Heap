#include <utility>
#include <vector>
#include <stdexcept>
#define SPACES "    "

template<typename KeyType, typename ValueType>
class Heap3 {
public:
    using KeyValueType = std::pair<KeyType, ValueType>;
	std::vector<KeyValueType> array;

	bool empty() const noexcept {
		if (array.size() == 0)
			return true;
		return false;
	}

	int findParent(int position) const {
		if (position == 0)
			return -1;
		else if (position % 3 == 0)
			return position / 3 - 1;
		else
			return position / 3;
	}

	unsigned findFirstChild(int position) const {
		return position * 3 + 1;
	}

	void insert(KeyType const & key, ValueType const & value) {
		KeyValueType keyValue;
		keyValue.first = key;
		keyValue.second = value;
		array.push_back(keyValue);
		int position = array.size() - 1;
		int parentPosition = findParent(position);

		while (parentPosition != -1) {
			if (array[position].first < array[parentPosition].first)
				std::swap(array[position], array[parentPosition]);
			else
				break;
			position = findParent(position);
			parentPosition = findParent(position);
		}
	}

	void insert(KeyValueType const & key_value) {
		insert(key_value.first, key_value.second);
	}

	KeyValueType const & peek() const {
		if (array.size() != 0)
			return array[0];
		else
			throw std::logic_error("Size == 0");
	}

	unsigned smallest(int child1, int child2, int child3) const {
		if (child3 == -1 && child2 == -1) {
			return child1;
		}
		if (child3 == -1) {
			if (array[child1].first <= array[child2].first)
				return child1;
			else
				return child2;
		}
		if (array[child1].first <= array[child2].first && array[child1].first <= array[child3].first)
			return child1;
		if (array[child2].first <= array[child1].first && array[child2].first <= array[child3].first)
			return child2;
		if (array[child3].first <= array[child1].first && array[child3].first <= array[child2].first)
			return child3;
		return 0;
	}

	KeyValueType pop() {
		if(array.size() == 0)
			throw "No element to pop. Size of heap is 0.";
		KeyValueType temp = array[0];
		
		std::swap(array[0], array[array.size() - 1]);
		array.pop_back();
		unsigned child;
		int position = 0;

		while (findFirstChild(position) < array.size()) {
			child = findFirstChild(position);
			int small;
			if (child + 1 >= array.size())
				small = child;
			else if (child + 2 >= array.size())
				small = smallest(child, child + 1, -1);
			else
				small = smallest(child, child + 1, child + 2);

			if (array[small].first < array[position].first)
				std::swap(array[small], array[position]);
			else
				break;
			position = small;
		}

		return temp;
	}

	size_t size() const noexcept {
		return array.size();
	}
	
	template<typename StreamType>
	void printRek(StreamType& stream, int position, int spaces) const {
		unsigned child = findFirstChild(position);
		if (child < array.size()) {
			for (int i = 0; i < spaces; i++)
				stream << SPACES;
			stream << array[child].first << std::endl;
			if (findFirstChild(child) < array.size())
				printRek(stream, child, spaces + 1);
		}
		if (child + 1 < array.size()) {
			for (int i = 0; i < spaces; i++)
				stream << SPACES;
			stream << array[child + 1].first << std::endl;
			if (findFirstChild(child + 1) < array.size())
				printRek(stream, child + 1, spaces + 1);
		}
		if (child + 2 < array.size()) {
			for (int i = 0; i < spaces; i++)
				stream << SPACES;
			stream << array[child + 2].first << std::endl;
			if (findFirstChild(child + 2) < array.size())
				printRek(stream, child + 2, spaces + 1);
		}
	}
	

	template<typename StreamType>
	void print(StreamType& stream) const {
		if (array.size() == 0)
			return;
		stream << array[0].first << std::endl;
		printRek(stream, 0, 1);
	}
};
