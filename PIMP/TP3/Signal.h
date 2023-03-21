#ifndef SIGNAL_H
#define SIGNAL_H

#include <vector>
#include <map>
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
	class Signal;

	template<typename R, typename... Args, typename Combiner>
	class Signal<R(Args...), Combiner> {
	public:
		using combiner_type = Combiner;
		using result_type = typename std::conditional<
					std::is_same<Combiner, VectorCombiner<typename std::function<R(Args...)>::result_type>>::value,
					std::vector<typename std::function<R(Args...)>::result_type>,
					typename std::function<R(Args...)>::result_type>::type;

		Combiner combiner;
		std::map<int, std::function<R(Args...)>> functions;
		int count = 0;

		Signal(Combiner c = Combiner()) {
			combiner = c;
		}

		std::size_t connectSlot(std::function<R(Args...)> callback) {
			functions[count] = callback;
			int save = count;
			count++;
			return save;
		}

		void disconnectSlot(std::size_t id) {
			functions.erase(id);
		}

		result_type emitSignal(Args... args) {
			for (size_t i = 0; i < functions.size(); i++) {
				if constexpr (std::is_same<result_type, void>::value) {
					functions[i](args...);
				} else {
					combiner.combine(functions[i](args...));
				}
			}
			if constexpr (!std::is_same<result_type, void>::value) {
				return combiner.result();
			}
		}
	};

}

#endif // SIGNAL_H
