// Copyright (c) 2019 YdeaGames
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
#pragma once

#include <new>
#include <type_traits>
#include <functional>

// Optional�N���X (���p��)
template <typename T>
class Optional {
public:
	// ���Optional
	Optional(std::nullptr_t it) : data(), data_pointer(nullptr) {}
	// ���g����Optional
	Optional(const T& it) : data(), data_pointer(new(&data) T(it)) {}
	// �R�s�[�R���X�g���N�^
	Optional(const Optional<T>& it) : data(), data_pointer(it ? new(&data) T(*it) : nullptr) {}
	// ���[�u�R���X�g���N�^
	Optional(Optional<T>&& it) noexcept : data(), data_pointer(it ? new(&data) T(std::move(*it)) : nullptr) {}
	// �����t��
	template <typename ...Args>
	Optional(Args ...args) : data(), data_pointer(new(&data) T(args...)) {}
	// �f�X�g���N�^
	~Optional() { if (data_pointer) data_pointer->~T(); }
	// ������Z�q (��)
	Optional<T> operator=(std::nullptr_t it) {
		if (data_pointer) data_pointer->~T();
		data_pointer = nullptr;
		return *this;
	}
	// ������Z�q�R�s�[
	Optional<T> operator=(const Optional& it) {
		if (data_pointer) data_pointer->~T();
		data_pointer = it ? new(&data) T(*it) : nullptr;
		return *this;
	}
	// ������Z�q���[�u
	Optional<T> operator=(Optional&& it) {
		if (data_pointer) data_pointer->~T();
		data_pointer = it ? new(&data) T(std::move(*it)) : nullptr;
		return *this;
	}
	// �l�擾
	T& operator*() const { return *data_pointer; }
	// �l�擾
	T* operator->() const { return data_pointer; }
	// �l�����邩�m�F
	operator bool() const { return data_pointer != nullptr; }
	// ��
	bool operator==(const Optional& it) const { return data_pointer == it.data_pointer; }
	// ��
	bool operator!=(const Optional& it) const { return data_pointer != it.data_pointer; }
	// ��łȂ���Ύ��s
	template <typename Func>
	void ifPresent(Func func) const { if (data_pointer) func(*data_pointer); }
	// ��łȂ���Ύ��s�����ʂ�Ԃ�
	template <typename Func>
	Optional<T> map(Func func) const
	{
		if (data_pointer) return func(*data_pointer);
		else return nullptr;
	}
	// true�ł���΂��̂܂܁Afalse�ł���΋��Ԃ�
	template <typename Func>
	Optional<T> filter(Func func) const
	{
		if (data_pointer)
			if (func(*data_pointer))
				return *this;
		return nullptr;
	}
	// �l�擾 or �f�t�H���g�l
	const T& orElse(const T& els) const { return data_pointer ? *data_pointer : els; }
	// �l�擾 or �f�t�H���g�l�����֐�
	template <typename Func>
	T orElseGet(Func func) const
	{
		if (data_pointer) return *data_pointer;
		else return func();
	}

private:
	// �f�[�^ (������������������A�v�����T�^������傫���̔�������Ă�)
	typename std::aligned_storage<sizeof(T), __alignof(T)>::type data;
	// �f�[�^�ւ̃|�C���^
	mutable T* data_pointer;
};