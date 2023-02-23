#ifndef CELLGENERATOR_H
#define CELLGENERATOR_H

#include <coroutine>
#include <memory>
#include "Cell.h"

class CellGenerator {
public:
    class promise_type {
        friend class CellGenerator;

    public:
        CellGenerator get_return_object();

        std::suspend_always initial_suspend();
        std::suspend_never  final_suspend() noexcept;

        void unhandled_exception();

        std::suspend_always yield_value(std::shared_ptr<Cell> cell);
        std::suspend_always return_void();

    private:
        std::shared_ptr<Cell> current_cell;
    };

    using handle_type = std::coroutine_handle<CellGenerator::promise_type>;

    explicit CellGenerator(handle_type handle);
    CellGenerator(const CellGenerator&) = delete;
    CellGenerator(CellGenerator&&);
    CellGenerator& operator=(const CellGenerator&) = delete;
    CellGenerator& operator=(CellGenerator&&);

    ~CellGenerator();

    std::shared_ptr<Cell> current_cell();

    std::shared_ptr<Cell> next_cell();


private:
    handle_type handle;
};

#endif // CELLGENERATOR_H
