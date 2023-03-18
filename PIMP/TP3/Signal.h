#ifndef SIGNAL_H
#define SIGNAL_H

#include <vector>
#include <functional>
#include <type_traits>

namespace sig {

	class DiscardCombiner {
	public:
		using result_type = void;

		template<typename U>
		void combine(U&& item) {
		}

		result_type result() {
		}
	};

	template<typename T>
	class LastCombiner {
	public:
		using result_type = T;
		T last;
		

		template<typename U>
		void combine(U&& item) {
			last = item;
		}

		result_type result() {
			return last;
		}
	};

	template<typename T>
	class VectorCombiner {
	public:
		using result_type = std::vector<T>;
		std::vector<T> all;

		template<typename U>
		void combine(U&& item) {
			all.push_back(item);
		}

		result_type result() {
			return all;
		}
	};

	template<typename Signature, typename Combiner = DiscardCombiner>
	class Signal {
	public:
		using combiner_type = Combiner;
		using result_type = typename std::function<Signature>::result_type;

		Combiner combiner;
		std::vector<std::function<Signature>> functions;
		Signal(Combiner c = Combiner()) {
			combiner = c;
		}

		std::size_t connectSlot(std::function<Signature> callback) {
			functions.push_back(callback);
			return functions.size() - 1;
		}

		void disconnectSlot(std::size_t id) {
			functions.erase(functions.begin() + id);
		}

		template<typename... Args>
		result_type emitSignal(Args... args) {
			for (size_t i = 0; i < functions.size(); i++) {
				if constexpr (std::is_same<result_type, void>::value) {
					functions[i](args...);
				} else {
					combiner.combine(functions[i](args...));
				}
			}
			if (std::is_same<result_type, void>::value) {
				return combiner.result();
			}
		}
	};

}

#endif // SIGNAL_H
