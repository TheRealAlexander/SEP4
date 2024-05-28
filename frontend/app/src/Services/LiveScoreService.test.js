import axios from 'axios';
import LiveScoreService from './LiveScoreService';

// Mock the axios module
jest.mock('axios');

describe('LiveScoreService', () => {
  it('fetches live score', async () => {
    // Setup the mocked response
    const mockedResponse = { data: { /* your mocked live score data */ } };
    axios.get.mockResolvedValue(mockedResponse);

    // Call the function
    const result = await LiveScoreService.getLiveScore();

    // Assert that the result is as expected
    expect(result).toEqual(mockedResponse.data);
  });

  it('fetches all matches', async () => {
    // Setup the mocked response
    const mockedResponse = { data: { /* your mocked matches data */ } };
    axios.get.mockResolvedValue(mockedResponse);

    // Call the function
    const result = await LiveScoreService.getAllMatches();

    // Assert that the result is as expected
    expect(result).toEqual(mockedResponse.data);
  });
});