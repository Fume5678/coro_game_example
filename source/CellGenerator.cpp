#include "CellGenerator.h"
#include <coroutine>
#include <exception>
#include <memory>
#include <iostream>

CellGenerator::CellGenerator(handle_type handle) : handle(handle) {}

CellGenerator::CellGenerator(CellGenerator&& other) : handle(other.handle) {
    other.handle = nullptr;
}

CellGenerator& CellGenerator::operator=(CellGenerator&& other) {
    handle       = other.handle;
    other.handle = nullptr;
    return *this;
}

CellGenerator::~CellGenerator() {
    if (handle) {
        handle.destroy();
    }
}

std::shared_ptr<Cell> CellGenerator::current_cell() {
    return handle.promise().current_cell;
}

std::shared_ptr<Cell> CellGenerator::next_cell() {
    if (!handle.done()) {
        handle.resume();
    }
    return handle.promise().current_cell;
}

// promise_type
CellGenerator CellGenerator::promise_type::get_return_object() {
    return CellGenerator{CellGenerator::handle_type::from_promise(*this)};
}

std::suspend_always CellGenerator::promise_type::initial_suspend() {
    return {};
}

std::suspend_never CellGenerator::promise_type::final_suspend() noexcept {
    return {};
}

void CellGenerator::promise_type::unhandled_exception() {
    std::cout << "[ERROR] Coroutine exception\n";
}

std::suspend_always
    CellGenerator::promise_type::yield_value(std::shared_ptr<Cell> cell) {
    current_cell = cell;

    return {};
}

std::suspend_always CellGenerator::promise_type::return_void() {
    return {};
}
