/*
Copyright (c) by respective owners including Yahoo!, Microsoft, and
individual contributors. All rights reserved.  Released under a BSD (revised)
license as described in the file LICENSE.
*/

#pragma once

#include "vw_clr.h"

namespace VW
{
	ref class VowpalWabbitExample;
	ref class VowpalWabbit;
	
	/// <summary>
	/// Interface for prediction factories enabling read-out of various prediction results in an extendable manner.
	/// </summary>
	generic<typename T>
	public interface class IVowpalWabbitPredictionFactory
	{
	public:
		/// <summary>
		/// Creates a new prediction result from an example and the associated VW instance.
		/// </summary>
		/// <returns>A prediction result.</returns>
		/// <remarks>Implementation must be thread-safe.</remarks>
		T Create(vw* vw, example* ex);
	};

	/// <summary>
	/// A scalar prediction result.
	/// </summary>
	public ref class VowpalWabbitScalarPredictionFactory sealed : IVowpalWabbitPredictionFactory<float>
	{
	public:
		/// <summary>
		/// Extracts prediction results from example.
		/// </summary>
		virtual float Create(vw* vw, example* ex) sealed;
	};

	/// <summary>
	/// A cost sensitive prediction result.
	/// </summary>
	public ref class VowpalWabbitCostSensitivePredictionFactory sealed : IVowpalWabbitPredictionFactory<float>
	{
	public:
		/// <summary>
		/// Extracts cost sensitive prediction results from example.
		/// </summary>
		virtual float Create(vw* vw, example* ex) sealed;
	};

	/// <summary>
	/// A multi label prediction result.
	/// </summary>
	public ref class VowpalWabbitMultilabelPredictionFactory sealed : IVowpalWabbitPredictionFactory<cli::array<int>^>
	{
	public:
		/// <summary>
		/// Extracts multilabel prediction results from example.
		/// </summary>
		virtual cli::array<int>^ Create(vw* vw, example* ex) sealed;
	};

	/// <summary>
	/// A topic prediction result.
	/// </summary>
	public ref class VowpalWabbitTopicPredictionFactory sealed : IVowpalWabbitPredictionFactory<cli::array<float>^>
	{
	public:
		/// <summary>
		/// Extracts prediction results from example. The predicted topics.
		/// </summary>
		virtual cli::array<float>^ Create(vw* vw, example* ex) sealed;
	};
	
	/// <summary>
	/// Provides convenient collection of all prediction types.
	/// </summary>
	public ref class VowpalWabbitPredictionType sealed abstract
	{
	public:
		/// <summary>
		/// Use for scalar predictions.
		/// </summary>
		static initonly VowpalWabbitScalarPredictionFactory^ Scalar = gcnew VowpalWabbitScalarPredictionFactory;

		/// <summary>
		/// Use for cost sensitive predictions.
		/// </summary>
		static initonly VowpalWabbitCostSensitivePredictionFactory^ CostSensitive = gcnew VowpalWabbitCostSensitivePredictionFactory;

		/// <summary>
		/// Use for multi label predictions.
		/// </summary>
		static initonly VowpalWabbitMultilabelPredictionFactory^ Multilabel = gcnew VowpalWabbitMultilabelPredictionFactory;

		/// <summary>
		/// Use for LDA topic predictions.
		/// </summary>
		static initonly VowpalWabbitTopicPredictionFactory^ Topic = gcnew VowpalWabbitTopicPredictionFactory;
	};
}