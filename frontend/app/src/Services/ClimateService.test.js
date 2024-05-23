import { act } from 'react';
import { renderHook } from '@testing-library/react-hooks';
import axios from 'axios';
import { useSensorData, setPreferredValue } from './ClimateService';

jest.mock('axios');

describe('ClimateService', () => {
    afterEach(() => {
        jest.clearAllMocks();
    });
    beforeAll(() => {
        jest.spyOn(console, 'error').mockImplementation(() => { });
    });

    afterAll(() => {
        console.error.mockRestore();
    });

    it('fetches sensor data', async () => {
        const data = [
          { temperature: 20, humidity: 30, CO2: 40 },
          { temperature: 21, humidity: 31, CO2: 41 },
        ];
        axios.get.mockResolvedValue({ data: data });
      
        const { result, waitForNextUpdate } = renderHook(() => useSensorData());
      
        await act(async () => {
          await waitForNextUpdate();
          expect(result.current.thermData).toEqual({ temperature: data[data.length - 1].temperature });
          expect(result.current.humidityData.humidity).toEqual(data[data.length - 1].humidity);
          expect(result.current.CO2Data).toEqual({ CO2: data[data.length - 1].CO2 });
        });
    });


    it('sets preferred values', async () => {
        const data = { message: 'Preferred values set successfully' };
        axios.post = jest.fn().mockResolvedValue({ data });

        const response = await setPreferredValue(1, 25, 50);

        expect(response).toEqual(data);
    });
});