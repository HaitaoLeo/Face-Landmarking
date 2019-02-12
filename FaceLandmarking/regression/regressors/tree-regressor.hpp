#pragma once 

#include <vector>
#include <filesystem>

#include "../../io/tree-io.hpp"
#include "../../math/vector.hpp"

namespace FaceLandmarking::Regression::Regressors
{
	namespace fs = std::experimental::filesystem;

	class TreeRegressor
	{
	private:
		std::vector<int> features;
		std::vector<float> thresholds;
		std::vector<int> leftChildren;
		std::vector<int> rightChildren;
		std::vector<float> values;

	public:
		TreeRegressor(fs::path path)
		{
			IO::TreeIO::load(path, features, thresholds, leftChildren, rightChildren, values);
		}

		float get(const std::vector<float>& features)
		{
			int node = 0;

			while (features[node] != -2)
			{
				if (features[features[node]] <= thresholds[node])
					node = leftChildren[node];
				else
					node = rightChildren[node];
			}

			return values[node];
		}
	};
}