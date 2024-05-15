export default {
    get: jest.fn(() => Promise.resolve({ data: {} })),
    create: jest.fn(function () {
      return this;
    }),
  };