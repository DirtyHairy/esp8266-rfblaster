#ifndef SIMPLE_QUEUE_H
#define SIMPLE_QUEUE_H

template <unsigned int size, class T> class SimpleQueue {
    public:

        SimpleQueue() : base(0), length(0) {}

        uint32_t getLength() const {
            return length;
        }

        bool push(T item) {
            if (length >= size) return false;

            items[(base + length++) % size] = item;

            return true;
        }

        bool pop(T& target) {
            if (length == 0) return false;

            target = items[base];

            base = (base + 1) % size;
            length--;

            return true;
        }

    private:

        T items[size];

        uint32_t base;
        uint32_t length;

    private:

        SimpleQueue(const SimpleQueue&) = delete;
        SimpleQueue(SimpleQueue&&) = delete;

        SimpleQueue& operator=(const SimpleQueue&) = delete;
        SimpleQueue& operator=(SimpleQueue&&) = delete;
};

#endif // SIMPLE_QUEUE_H
